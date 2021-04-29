# Doom3D

Software rasterized game engine with 3d editor and demo maps

Features:
- Raycasted 3D (ray to triangle corners, screen intersection for rasterization)
- Parallel rendering with z-sorted triangles
- Depth shading + Simple Lights
- Normal mapping capability
- `.obj` file import and usage for world generation
  - homemade 3d models :)
- Full 3D map / scene editor
- Kd tree for raycast intersections & collision help
- AABB collision (player)
- AABB viewbox occulsion for objects & triangles
- Skybox
- A* path finding and node-based npc paths
- 3D animations (from frames)
- 2D sprite effects
- Music & effects with SDL_mixer
- Fancy logs
- Debug lines
- Custom events for engine logic with SDL user events

## Installation

### Mac

1. Clone & Run :)

```sh
git clone https://github.com/hakolao/doom3d && cd doom3d
make && ./doom-nukem
```

### WSL

1. Install SDL2, SDL_image, SDL_ttf and SDL_mixer on WSL terminal on windows
2. Install vcxsrv on Windows
3. Run

```
sudo apt update
sudo apt-get install xorg-dev # make sure x11 related stuff is installed
# install sdl
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
# install vcxsrv on windows side & run it
export DISPLAY=:0
export LIBGL_ALWAYS_INDIRECT=1
# run doom3d
git clone https://github.com/hakolao/doom3d && cd doom3d
make && ./doom-nukem
```

### Linux

1. Install SDL2, SDL_image, SDL_ttf and SDL_mixer on Linux
2. Run

```sh
sudo apt update
sudo apt-get install xorg-dev # make sure x11 related stuff is installed
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
git clone https://github.com/hakolao/doom3d && cd doom3d
make && ./doom-nukem
```
