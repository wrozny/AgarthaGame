# AgarthaGame
Game about bad people going to agartha, you have to protect the land.

# How to build?
<p>I'm using cmake for this project.</p>

## Windows:
Make a build directory inside the AgarthaGame repository copy:
```
mkdir build
cd build
```

Configure the project:
```
cmake ..
```

Build the project:
```
cmake --build . --config Release
```

The final executable will be inside build/Release

## Ubuntu (24.04):
Will work the same as above but make sure to have OpenGL support and libx11!
```
sudo apt install libgl1-mesa-dev
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxkbcommon-dev
```
