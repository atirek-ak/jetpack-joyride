Project by Atirek Kumar 
Github Link: https://github.com/atirek-ak/

NOTE: This code is designed to run on Mac OS

Adapted From : https://github.com/sidgairo18/Graphics_Spring_19_Boilerplate.git

Install Opengl: 
You need to install the development packages of the following libraries:
GLEW
GLFW3
GLM

# Install homebrew
brew install glew glfw glm cmake pkg-config


Make instructions: (or directly run this script using 'bash make.sh')
mkdir build
cd build
cmake ../
make all -j 4

Note - In case of Experimental Error for GLM.
add "#define GLM_ENABLE_EXPERIMENTAL" in the files main.h nonedit.cpp other_handlers.cpp and input.cpp, before you include glm.


GAME CONTROLS:
'Space' to activate jetpack
Arrow keys or 'a' and 'd' to move left and right
'F' to throw water balloon

Features
- Firelines
- FireBeams
- Power-Ups(Blue restores health to 100. Yellow gives 100 point)
- Coins(Blue:20. Red:10)
- Boomerang obstacle
- Magnet 
- Gravity
- Score(on left) and Health(on right) displayed 
- Throw Water Balloon
