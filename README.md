# Jetpack Joyride
A basic version of the popular mobile game Jetpack Joyride    
Designed to run to Mac OS

## Getting Started
### Install Opengl
You need to install the development packages of the following libraries:
* GLEW
* GLFW3
* GLM  

To do so, run the command:  
```brew install glew glfw glm cmake pkg-config```

### Make instructions: (or directly run this script using  ```bash make.sh```)
* mkdir build
* cd build
* cmake ../
* make all -j 4

## To run the game
- Go to build directory
- ```./graphics_asgn1```  
Note - In case of Experimental Error for GLM add ```#define GLM_ENABLE_EXPERIMENTAL``` in the files main.h, nonedit.cpp, other_handlers.cpp and input.cpp before you include glm.


## GAME CONTROLS:
* 'Space' to activate jetpack
* Arrow keys or 'a' and 'd' to move left and right
* 'F' to throw water balloon

## Features
- Firelines
- FireBeams
- Power-Ups(Blue restores health to 100. Yellow gives 100 point)
- Coins(Blue:20. Red:10)
- Boomerang obstacle
- Magnet 
- Score(on left) and Health(on right) displayed 
- Throw Water Balloon

## Built using
- C++
- OpenGL

## Author
Atirek Kumar  
Github Handle Link: https://github.com/atirek-ak/

## Acknowledgement
Boilerplate : https://github.com/sidgairo18/Graphics_Spring_19_Boilerplate.git
