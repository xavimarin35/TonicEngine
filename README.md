# Tonic Engine

[Tonic Engine](https://github.com/xavimarin35/TonicEngine) is a 3D Game Engine developed in C & C++ made by Pol Casaú and Xavi Marín, students of [CITM](https://www.citm.upc.edu/) in Barcelona during our [Game Design and Development Bachelor's Degree](https://www.citm.upc.edu/cat/estudis/grau-videojocs-bcn/). This engine specializes in the User Interfaces subsystem.

## Features

### Windows

**Main Tab:**
Menus of all the functionalities of the engine
* File
* GameObject
* Debug
* Windows
* Help

**Scene Viewport:**
Displays the scene from the view of the editor camera
* Shows the ImGizmos

**Game Viewport:**
Displays the scene from the view of the play camera
* Maintain the proper aspect ratio when is resized

**Hierarchy:**
Shows current GameObjects tree
* Reparent with drag and drop
* Creation and deletion of GameObjects
* Current active Game Camera

**Inspector:**
Shows the attributes of the selected GameObject
* Transform, Mesh, Texture and Camera components
* Rename and enable/disable of GameObjects
* Change properties of the components

**Console:**
Logs real-time information about the engine's processes
* Autoscroll
* Clear console and last log buttons
* Different colors depending on log type

**Configuration:**
Shows the properties of the engine and its rendering
* Application, Hardware and Input information
* Window and Rendering options
* Camera movement sensitivity

**Assets:**
Displays all the resources used by the engine and their information
* Meshes, textures and models folder
* Textures can be assigned from the folder to current selected GameObject
* Models can be imported to current scene from the folder

**State:**
Contains the Play menu and other important buttons
* Move, Rotate and Scale buttons for gizmos
* Bounding boxes buttons
* Playmode buttons

### User Interface System

This engine is specialized in the User Interface system:

* You can create a parent canvas to contain all the UI elements
* You can create an image and assign it any picture
* You can create a button and assign a function to it

![CREATION OF UI ELEMENTS](https://github.com/xavimarin35/TonicEngine/blob/gh-pages/docs/gifs/Create.gif?raw=true)

In this gif we see how we create different UI elements that automatically place inside the canvas

![FUNCTION OF BUTTON](https://github.com/xavimarin35/TonicEngine/blob/gh-pages/docs/gifs/PlayMode.gif?raw=true)

In this gif we see how, when the game starts, by pressing RETURN, the main menu disappears and the scene is loaded

### Functionalities

* **Resource Manager:** Manages all the assets of the engine
* **Mouse Picking:** GameObjects can be picked from the world using the mouse
* **Drag & Drop:** Meshes and Textures can be dropped to the engine
* **Playmode:** The engine enters into a simulation with the active game camera
* **Bounding Boxes:** All meshes have their own AABB
* **Own file format:** New meshes and textures are saved in the library
* **Frustum culling:** Cameras can discard and don't draw elements outside their range of view
* **Scene Serialization:** Scenes information can be saved into .json files

### Extra Features

* Docking
* ImGizmos
* Debug Menu
* Environment customization

## Usage

### Installation

Download the zip file and unzip it. Open the folder, execute the .exe and enjoy Tonic Engine!

IMPORTANT: *Do not modify, change or add any folder or file (unless specified) as you might not be able to execute the application.*

### Camera Controls

* **Right Click**: First-Person Camera
* **Right Click + WASD / QE**: Move camera in different directions.
* **Shift + Movement**: Duplicates camera velocity.
* **ALT + Left Click**: Orbit around reference point.
* **Mouse Wheel Scroll** or **ALT + Right Click**: Zoom in / Zoom out.
* **Mouse Wheel Drag**: Move camera through the actual axis.
* **F**: Focus camera to selected Game Object.

### Shortcuts

* **CTRL + S:** Saves the actual scene information
* **CTRL + A:** Loads the saved scene
* **CTRL + R:** Resets the transform of the selected GameObject
* **CTRL + T:** Saves the actual transform of the GameObject to be the new default
* **W / E / R:** Move / Rotate / Scale gizmo operation
* **SUPR:** Deletes the selected GameObject
* **ESC:** Activates/Deactivates the Exit Engine pop-up
* **ALT + F4:** Closes the engine

## Pol Casaú

![](https://github.com/xavimarin35/TonicEngine/blob/gh-pages/docs/images/pol_.jpg?raw=true)

- Github: [Bullseye14](https://github.com/Bullseye14)
- LinkedIn: [Pol Casaú](https://www.linkedin.com/in/polcasau8/)

### Individual Work

- FBX import and Drag & Drop
- DevIL and Textures import
- GameObjects' Components
- Module Camera Improvement (v2)
- Work on all of the panels
- Own File Format
- Gizmos implementation
- Bounding Boxes
- Frustum and Camera Culling
- Mouse Picking
- Camera to Component (v3)
- Reparenting
- Main Menu
- Website
	
## Xavi Marín

![](https://github.com/xavimarin35/TonicEngine/blob/gh-pages/docs/images/xavi.jpg?raw=true)

- Github: [XaviMarin35](https://github.com/xavimarin35)
- LinkedIn: [Xavi Marín](https://www.linkedin.com/in/xavi-marin-sola/)

### Individual Work

- Panels system and docking
- Engine Icon
- Work on all of the panels
- Module Camera (v1)
- GameObjects system
- Vertex and Face normals
- GameObjects' parenting
- Json implementation
- Gizmos implementation
- Playmode logic
- Scene and Game Viewports
- Resource Manager
- UI Base System
- Canvas, buttons and images

## Contact

 Don't hesitate to visit:
 - Our repository: [Tonic Engine](https://github.com/xavimarin35/TonicEngine) 
 - Latest Release: [Releases](https://github.com/xavimarin35/TonicEngine/releases)
 
 Or contact us:
 - Pol Casaú: pccpolcasau@gmail.com
 - Xavi Marín: xmarin98@gmail.com
 
  
## Third Party Libraries

* [SDL](https://www.libsdl.org/)
* [OpenGL](https://www.opengl.org/)
* [ImGui](https://github.com/ocornut/imgui)
* [glew](http://glew.sourceforge.net/)
* [ASSIMP](http://assimp.org/)
* [DevIL](http://openil.sourceforge.net/)
* [MathGeoLib](https://github.com/juj/MathGeoLib)
* [PCG](https://www.pcg-random.org/index.html)
* [PhysFS](https://icculus.org/physfs/)
* [JSON](https://github.com/nlohmann/json)

## License

Licensed under the [MIT License](https://github.com/xavimarin35/TonicEngine/blob/master/LICENSE)
