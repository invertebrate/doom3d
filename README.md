# Doom3D

Video Showcase: https://youtu.be/BQTTFh3VMtQ

Software rasterized raycast projected game engine with 3d editor and demo maps

----------------------------------------
This was a group project part of the 42 curriculum. It was built on our earlier Wolf3d-rasterizer project using its engine. 
My areas of focus in this project were:

**Rendering**
- Projection methon using rays
- Triangle processing
- Texture and normal mapping
- Triangle rasterization
- Shading and lighting

**Animations**
- An makeshift animation system that used multiple 3D objects in different poses as animation frames.
- Animation timers and triggers based on animation state

**Physics**
- Player collider and physics interaction
----------------------------------------

Features:
- Raycasted 3D (ray to triangle corners, screen intersection for rasterization)
- Parallel rendering with z-sorted triangles
- Depth shading + Simple Lights
- Normal mapping capability
- `.obj` file import and usage for world generation
  - homemade 3d models :)
- Full 3D map / scene editor
- Kd tree for raycast intersections & collision help
- AABB & ray collision
- AABB viewbox occulsion for objects & triangles
- Skybox
- A* path finding and node-based npc paths
- 3D animations
- 2D sprite effects
- Triggers
- Music & effects with SDL_mixer
- Fancy logs
- Debug lines
- Custom events
- ... lots more

## Installation

### Mac & Linux

Windows is not supported

1. Clone & Run :)

```sh
git clone https://github.com/hakolao/doom3d && cd doom3d
make && ./doom-nukem --default

# to create a standalone version run
./doom-nukem --convert-assets
# save first map in editor and then you can move
# the executable, levels, level_list.txt elsewhere and run standalone
./doom-nukem
```

Created as part of Hive Helsinki Graphics Path:
- @hakolao
- @invertebrate
- @ahakanen
- @RandommUser
