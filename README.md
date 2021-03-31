# Doom3D

Features:

- Raycasted 3D
- Parallel rendering
- Depth shading
- Option for simple normal mapping
- `.obj` file import and usage for world generation
  - homemade 3d models :)
- AABB collision (player)
- AABB viewbox occulsion
- Skybox

## Install

### Mac

1. Clone & Run :)

```sh
git clone https://github.com/hakolao/doom3d && cd doom3d
make && ./doom3d
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
make && ./doom3d
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
make && ./doom3d
```
