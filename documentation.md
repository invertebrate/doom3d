# Documentation

## Rendering

![Render flowchart](assets/img/render_architecture.jpg)

- Objects & triangles are culled based on camera viewbox
- Remaining triangles are copied and pushed to a vector of render triangles
- Render triangles are sorted by z depth (to fasten depth testing worst cases (depends on viewing angle))
- Transparent triangles are handled separately in their own vector
- In parallel (two passes, one for regular triangles another for transparent):
  - Buffers are cleared
  - Triangles are rasterized
  - Buffers are drawn onto main buffer
- Main buffer will then be presented onto window

## Libs

Easiest way to learn how to use a function is to cmd+shift+f (app wide search) in your IDE and see where a function has been used.

- `lib3d`: 3d library holding all data structures and functionality that are general and not specific to doom3d.
  - 2D line drawing with clipping outside bounds
  - Rasterization & shading
  - Pixel plotting
  - Useful data structs
  - 3d .obj file reading
  - 3d object instantiation
  - bmp image reading
  - image placement from surface to surface (e.g. bmp onto framebuffer)
  - Kd-tree for ray casting with triangles
  - Ray intersection tests for bounding boxes and triangles
  - Triangle sorting by morton code or depth
- `libgmatrix`: Vector and matrix math
- `libft`: c stdlib style functions and useful added functions on top of those
  - Hash(map/table), see `scene/assets/c` for usage, or `libft/tests`
  - Threadpool (see usage in `src/render/render.c`: `render_work_parallel` & `src/doom3d.c`: `doom3d_run`)
  - File reading (See `l3d_read_obj` for usage)
  - Parallel radix sort
  - Logging implementation
