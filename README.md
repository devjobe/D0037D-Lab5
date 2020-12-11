# D0037D Lab 5

```yaml
User: ojaebh-0  
Time estimate: 3h
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

Task3.

Task 3: Design classes for a city-building game
Use a UML modeling tool (e.g. Visual Paradigm, Modelio, UMLet, VioletUML, Draw.io, etc.) to design a class diagram for a city-building game (e.g. a light version of SimCity). 

Objects:

* World // Object user interacts with
	* Map
		- Size
		- Tile
			- elevation
			- waterpipe
			- power line
			- is powered
			- is water connected
			- Zoning // per tile
				* type: ZoningType
						* fields 
							- developmentRate
						* Residence 
						* Commercial
						* Industry
				- developmentStage
		- Trees
			- x,y
		- Waterlevel 
		- Constructions
			* Road
				- RoadType
			* Facility
				* Power station
				* Police Department
				* Fire Department
				* School
				* Hospital

		- Selection
	- build()
	- save()
	- load()
	- setSimulationSpeed()
	- update()
	- money



* Selection
	- x0, y0, x1, y1

* BuildTool
	* SelectTool
	* BeginSelection
	* UpdateSelection
	* EndSelection



Think:
What classes are needed to represent different objects in the game?
How are these classes related?
Can you identify any inheritance? (IS-Arelationships)
Can you identify any composition? (HAS-Arelationships)

What fields do the classes have?
What methods do the classes have (except getters and setters)?

Which of the classes are abstract, and which are concrete?
In abstract classes, which of the methods are abstract?

Aim for an architecture of at least 10-15 classes, and use inheritance, composition and abstract class(es).



## Reflection

> What did you learn? What did you know already?

I learned the basics of SDL2 and the initial steps to creating a cross platform project using cmake. 
I knew how to use inheritance and encapsulation, abstract classes and polymorphism. 
I learned how to design UML class diagrams.

> What was difficult in the lab? How did you overcome it?

Task 1 and 2 went smoothly. Using vcpkg/cmake made the process very easy. Obviously would of been easy downloading SDL2 and adding manually as well.

> How can the lab be improved?



> Additionally, write an estimate how many hours you spent on this lab.

About 3h for task 1 and 2.