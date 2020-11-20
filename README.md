# nosur_render

A soft renderer based on graphics pipeline.

## Build

It runs on Windows and build with Visual Studio 2019

1. Add [OBJ_Loader](https://github.com/Bly7/OBJ-Loader) to the project
2. Add [stb/](https://github.com/nothings/stb) stb_image.h and stb_image_write.h to the project
3. Build and run
   
## Rendering pipeline

- Geometry Processing
  - Model transform
  - View transform
  - Projection
- Rasterization
  - Triangle traversal
  - Pixel processing
  - Blinn-phong shading
  - Texture mapping

## Samples

- Normal shading

<img src="https://github.com/chronoby/nosur_render/blob/master/output/normal.png" width="700"  alt="Normal shading"/><br/>

- Blinn-phong shading

<img src="https://github.com/chronoby/nosur_render/blob/master/output/phone.png" width="700"  alt="Blinn-phong shading"/><br/>

- Blinn-phong shading with texture

<img src="https://github.com/chronoby/nosur_render/blob/master/output/texture.png" width="700"  alt="with texture"/><br/>

## Something to be done

- Clipping
- Blending
- Mipmap
- Anti-aliasing
- optimizing
- ...

## Why "nosur_render"

"nosur_render" means No Surrender!
