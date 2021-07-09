# engine3d
A simple 3d engine to learn computer 3d graphics basics like Rotation, Projection, Camera etc.

All this stuff is made from scratch for study purpose, OpenGl/FreeGlut are used just to set the graphics environment and draw triangles.

C++/Open GL/FreeGlut

Requirements

    - FreeGlut 3.0.0 MSVC - https://www.transmissionzero.co.uk/software/freeglut-devel/
    - Visual Studio 2019

Run

    - Copy freeglut.dll 32 bits to system32 and freeglut.dll 64 bits to SysWOW64
    - Copy freeglut.dll to project root
    - Open project in VS 2019+, right click on project -> properties -> config -> linker -> entry -> addicional dependencies -> set freeglut.lib
