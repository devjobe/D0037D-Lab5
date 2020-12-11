# D0037D Lab 5

```yaml
User: ojaebh-0  
Time estimate: 8h
Visual Studio version: 2019 (cmake project)
```

## Build 

Requirements:
* cmake (minimum 3.8) (as component of Visual Studio installer)
* sdl2 package

### Installing vcpkg and sdl2

> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg install sdl2:x64-windows

Can be cloned/installed anywhere on your system.

### Building with Visual Studio

> .\vcpkg\vcpkg integrate install

Then open repo folder in Visual Studio and build.

#### Alternativly from Visual Studio Developer command prompt

> cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake

> cmake --build [build directory]

This will also create a Visual Studio solution for your system.

## Usage

From the build either run Lab5_Task1.exe or Lab5_Task2.exe (Selectable in the debug run menu in Visual Studio or run from command prompt).

Lab5_Task2.exe keybindings:
* esc/q - exits
* r - creates random rectangle
* t - creates random triangle
* c - creates random circle
* x - clears screen

## Reflection

> What did you learn? What did you know already?

I learned the basics of SDL2 and the initial steps to creating a cross platform project using cmake. 
I knew how to use inheritance and encapsulation, abstract classes and polymorphism. 
I learned how to design UML class diagrams.

> What was difficult in the lab? How did you overcome it?

Task 1 and 2 went smoothly. Using vcpkg/cmake made the process very easy. Obviously would of been easy downloading SDL2 and adding manually as well.

It was hard to limit the scope of task 3 so I decided to keep it on 1 A4 page and not work too long on it (turn in at the set date). 

> How can the lab be improved?

I will push a commit if I think of anything.

> Additionally, write an estimate how many hours you spent on this lab.

About 3h for task 1 and 2. About 5h for task 3.