# 3D-CollisionSimulator
A 3D model to simulate different types of elastic and inelastic collisions between multiple objects, using OpenGL Utility Toolkit.
How to run the code:
To run the code, type in the terminal:
~$ g++ Collision.cpp -lGL -lGLU -lglut
~$ ./a.out
The console will ask the user to enter the space key. User inputs for the simulation will be asked in the new window opened.

There are two input methods and as the user clicks on the required option or types in the values of given parameters,
values will appear in the console. After all the values have been inputted, the simulation will start.
During the simulation, changing velocities of the particles can be seen on the screen.
Simulation can be paused/resumed by pressing the space key or left-clicking the mouse.
After pressing X (shift+x), the window will close.

Components of the model:
The code is written in C++ using OpenGL Utility ToolKit. User input is taken using the keyboard as well as mouse.
The text is written in the window for input instructions as well as for showing the velocities.
Boundaries and the objects are in 3D and are colored. There is a constant light source from where shading can be seen on the moving objects.
Also, texture is added in the background.
