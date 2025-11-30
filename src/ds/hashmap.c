#include "ds/hashmap.h"

/*
    Creates new instance of m_node1d_t
*/
static inline m_node1d_t* NodeCreate(const char* key, void* data) {
    m_node1d_t *newNode = (m_node1d_t*) malloc(sizeof(m_node1d_t));

    if(!newNode) {
        return NULL;
    }

    newNode->data = data;
    newNode->key = strdup(key);

    if (!newNode->key) {
        free(newNode);
        return NULL;
    }


    newNode->next = NULL;

    return newNode;
}

/*
    Frees the node of a linked list
*/
static inline void NodeFree(m_node1d_t* node) {
    free((char*)node->key);
    free(node->data);
    free(node);
}

/*
    Frees all the nodes of a linked list
*/
static inline void NodeFreeList(m_node1d_t* head) {
    m_node1d_t *currentNode = head;

    while(currentNode) {
        m_node1d_t *nodeToFree = currentNode;
        currentNode = currentNode->next;
        NodeFree(nodeToFree);
    }
}

/*
    Frees all the nodes of a list 
*/
static inline void NodeFreeListDeep(m_node1d_t* head, void (*free_fn)(void*)) {
    m_node1d_t *currentNode = head;

    while(currentNode) {
        m_node1d_t *nodeToFree = currentNode;
        currentNode = currentNode->next;
        free_fn(nodeToFree->data);
        NodeFree(nodeToFree);
    }
}

/*
    Adds new node at the end of linked list or updates already existing key with new
    value address void pointer
*/
static inline void NodeUpdate(m_node1d_t *startNode, const char* key, void* valueAddr) {
    m_node1d_t *currentNode = startNode;
    
    while(currentNode->next) {
        if(strcmp(currentNode->key, key) == 0) {
            currentNode->data = valueAddr;
            return;
        }
        currentNode = currentNode->next;
    }
    
    currentNode->next = NodeCreate(key, valueAddr);
}

/*
    Returns void pointer to the data of a node with matching key
*/
static inline void* NodeFindValue(m_node1d_t* startNode, const char* key) {
    m_node1d_t* currentNode = startNode;

    while(currentNode) {
        if(strcmp(currentNode->key, key) == 0) {
            return currentNode->data;
        }

        currentNode = currentNode->next;
    }

    return NULL;
}


/*
    Removes node inside the linked list
*/
static inline void NodeRemove(m_node1d_t* startNode, const char* key) {
    m_node1d_t* previousNode = NULL;
    m_node1d_t* currentNode = startNode;


    while(currentNode) {
        if(strcmp(currentNode->key, key) == 0) {
            if(previousNode) {
                previousNode->next = currentNode->next;
            }
            NodeFree(currentNode);
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }
}

/*
    Prints out the linked list
*/
static inline void NodePrint(m_node1d_t *startNode) {
    m_node1d_t *currentNode = startNode;

    while(currentNode) {
        printf("Node('%s') -> ", currentNode->key);
        currentNode = currentNode->next;
    }

    printf("End\n");
}

/*
    Returns the length of a linked list
*/
static inline int NodeGetListLength(m_node1d_t *head) {
    m_node1d_t *current = head;

    int count = 0;

    while(current) {
        count++;
        current = current->next;
    }

    return count;
}


/*
    Allocates memory for new map instance
*/
Map* MapCreate(size_t initialCapacity) {
    if (initialCapacity == 0) {
        return NULL;
    }

    Map *newMap = (Map*) malloc(sizeof(Map));

    if(!newMap) {
        return NULL;
    }

    newMap->capacity = initialCapacity;
    newMap->buckets = calloc(initialCapacity, sizeof(m_node1d_t));

    if(!newMap->buckets) {
        free(newMap);
        return NULL;
    }

    return newMap;
}

/*
    Frees the map from memory
*/
void MapFree(Map* map) {
    if(!map) {
        return;
    }

    for(size_t i = 0; i < map->capacity; i++) {
        m_node1d_t *head = &map->buckets[i];
        
        if(head->next) {
            free((char*)head->key);
            free(head->data);
            NodeFreeList(head->next);
        }
    }

    free(map->buckets);
    free(map);
}

/*
    Expands the size of a map resulting in less collision.
    doubled automatically when 12:16 elements to capacity ratio reached
*/
void MapExpand(Map* map, size_t newCapacity) {
    if (!map) {
        return;
    }

    if(newCapacity < map->capacity) {
        return;
    }

    
}

/*
    Sets the value of a key to the value address in the map
*/
void MapSet(Map* map, const char* key, void* valueAddr) {
    if(!map) {
        return;
    }

    hash64 currentHash = Hash_fnv_1a64(key);
    m_node1d_t *targetBucket = &map->buckets[currentHash % map->capacity];

    if(targetBucket->key == NULL) {
        targetBucket->key = strdup(key);
        targetBucket->data = valueAddr;
        return;
    }

    NodeUpdate(targetBucket, key, valueAddr);
}

/*
    Removes the value with given key from the map
*/
void MapRemove(Map* map, const char* key) {
    if(!map || !key) {
        return;
    }

    hash64 currentHash = Hash_fnv_1a64(key);
    m_node1d_t *targetBucket = &map->buckets[currentHash % map->capacity];

    if(!targetBucket->key) {
        return;
    }

    if(strcmp(targetBucket->key, key) == 0) {
        if(!targetBucket->next) {
            targetBucket->data = NULL;
            targetBucket->key = NULL;
            targetBucket->next = NULL;
            return;
        }

        m_node1d_t *copiedValue = targetBucket->next;

        free((char*)targetBucket->key);

        targetBucket->data = targetBucket->next->data;
        targetBucket->key = targetBucket->next->key;
        targetBucket->next = targetBucket->next->next;

        free(copiedValue);
        return;
    }

    NodeRemove(targetBucket, key);
}

/*
    Returns pointer to the value with given key or null if key isn't set
*/
void* MapGet(Map* map, const char* key) {
    if(!map || !key) {
        return NULL;
    }

    hash64 currentHash = Hash_fnv_1a64(key);
    m_node1d_t *targetBucket = &map->buckets[currentHash % map->capacity];

    if(targetBucket->key == NULL) {
        return NULL;
    }

    return NodeFindValue(targetBucket, key);
}


/*
    Prints out every populated bucket inside the map
*/
void MapPrint(Map* map) {
    printf("Map {\n");

    for(size_t i = 0; i < map->capacity; i++) {
        m_node1d_t *bucket = &map->buckets[i];

        if(bucket->key) {
            printf("    Bucket %u(%d): ", (unsigned int)i, NodeGetListLength(bucket));
            NodePrint(bucket);
        }
    }

    printf("}\n");
}

// /*
//     Wrapper for dbg
// */
// void MapDebug() {
//     #ifdef DEBUG
//         dbg_printMemoryRaport();
//     #endif
// }