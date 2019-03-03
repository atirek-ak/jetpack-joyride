#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coins.h"
#include "power.h"
#include "background.h"
#include "fireBeams.h"
#include "boomerang.h"
#include "fireLines.h"
#include "digit.h"
#include "segmentdisplay.h"
#include "magnet.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform platform1;
Coins coins1[100];
Coins coins2[100];
Background background1;
FireBeams fireBeams1[12];
Boomerang boomerang1[12];
FireLines fireLines1[12];
FireBeams2 fireBeams2[12];
Segmentdisplay seg,seg2;
Magnet magnet1;

Beam beam1[12];
Power power1, power2, power3;
int score = 0, beamOn[12], health=100, magnet_timer=0,shot=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, my_center_x=0,my_center_y=0;
float camera_rotation_angle = 0;
bounding_box_t player_box;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( screen_center_x, screen_center_y, 1 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (screen_center_x, screen_center_y, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    background1.draw(VP);
    platform1.draw(VP);
    if((int)my_center_x%40<1 && magnet_timer==0)
    {
        magnet_timer+=1;
    }
    else if(magnet_timer<180 && magnet_timer>0)
    {
        magnet1.set_position(my_center_x + 3.0f,my_center_y + 3.0f);
        magnet1.draw(VP);
        magnet_timer+=1;
        attract();
    }
    else if(magnet_timer==180)
    {
        magnet_timer=0;
    }
    for(int i=0;i<100;i++)
    {
        coins1[i].draw(VP);
    }
    for(int i=0;i<100;i++)
    {
        coins2[i].draw(VP);
    }
    power1.draw(VP);
    power2.draw(VP);
    if(shot)
    {
        power3.draw(VP);
    }
    for(int i=0;i<12;i++)
    {
        boomerang1[i].draw(VP);
        fireBeams1[i].draw(VP);
        fireBeams2[i].draw(VP);
        if(beamOn[i])
            beam1[i].draw(VP);
        fireLines1[i].draw(VP);
    }
    ball1.draw(VP);
    seg.draw(VP);
    seg2.draw(VP);
    seg.update(score);
    seg2.update(health);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
    if (left || a) {
        ball1.position[0]-=0.05f;
    }
    else if(right || d){
        ball1.position[0]+=0.05f;
    }
    else if(up){
    	ball1.speed+=0.05f;
    }
    else if(f && shot ==0)
        shot = 1;
}

void attract(){
    ball1.position.x +=0.01f;
    if(ball1.position.y < 3.0f)
    ball1.speed +=0.0212f;
}

void player_checks(){
	ball1.speed -= 0.02f;
    ball1.position[1]+=ball1.speed/5;
    if(ball1.position[1]<0.0f)
    {
    	ball1.speed=0;
    	ball1.position[1]=0.0f;
    }
    if(ball1.position[1]>6.25f)
	{
    	ball1.position[1]=6.25f;
    	ball1.speed=0;
	}
    if(ball1.position[0]<0.0f + my_center_x)
    {
        ball1.position[0]=0.0f + my_center_x;
    }
    else if(ball1.position[0]>7.75f + my_center_x)
        ball1.position[0]=7.75f + my_center_x;
}

void update_positions(){
    my_center_x +=0.03f;
    screen_center_x +=0.03f;
    ball1.position[0]+=0.03f;
    platform1.position[0]=my_center_x;

    //Power Up 1
    if(-my_center_x + power1.position.x < 5.0f)
    {
        power1.position.x -= 0.01f;
        float dist = 2.0f - power1.position.y;
        power1.position.y += (power1.speed + dist)/30.0f;
        power1.speed += dist/(abs(dist)*7.0f);
    }

    //Power Up 2
    if(-my_center_x + power2.position.x < 5.0f)
    {
        power2.position.x -= 0.01f;
        float dist = 2.0f - power2.position.y;
        power2.position.y += (power2.speed + dist)/30.0f;
        power2.speed += dist/(abs(dist)*7.0f);
    }

    //Water Balloon/Power Up 3
    if(shot)
    {
        power3.position.x+=0.08f;
        power3.speed -= 0.02f;
        power3.position[1]+=power3.speed/5;
        if(power3.position.y < -2.5 || power3.position.y > 3.5)
            shot=0;
    }
    else
    {
        power3.speed=0.6f;
        power3.set_position(ball1.position.x-4 + 0.75f,ball1.position.y-3+0.5f);

    }

    //FireBeams
    for(int i=0;i<12;i++)
    {
    if(fireBeams1[i].position.x - my_center_x < 5.0f)
    {
        fireBeams1[i].position.x+=0.03f;
        fireBeams2[i].position.x+=0.03f;
        fireBeams1[i].time+=1;
        if(fireBeams1[i].time>300)
        {
        fireBeams1[i].position.y = -10.03f;
        fireBeams2[i].position.y = -10.03f;
        }
        else if(fireBeams1[i].time>240)
        {
            beamOn[i]=0;
        }
        else if(fireBeams1[i].time>60)
        {
            beamOn[i]=1;
            beam1[i].position.x+=0.03f;
        }
    }
    }

    //Boomerang
    for(int i=0;i<12;i++)
    {
        if(boomerang1[i].position.x < my_center_x - 2.5f && boomerang1[i].position.y > my_center_y)
        {
            boomerang1[i].speed += (my_center_y - boomerang1[i].position.y)/500.0f;
            boomerang1[i].position.y += 1 * boomerang1[i].speed;
        }
        else
        {
         if(boomerang1[i].position.y < my_center_y)
            boomerang1[i].position.x +=0.1f;
        else if(boomerang1[i].position.y > my_center_y)
            boomerang1[i].position.x -=0.1f;
    }
        boomerang1[i].rotation += 8.0f;
    }

    //Scoreboard
    seg.set_position(platform1.position.x - 5.0f,platform1.position.y - 3.5f);
    seg2.set_position(platform1.position.x - 3.0f,platform1.position.y - 3.5f);
}

/*void tick_elements() {
    if(my_center_x>40 && (int)my_center_x%40<10)
    {
        for(int i=0;i<5;i++)
        {
            if(my_center_x - fireBeams1[i].position.x > 5.0f)
            {
                fireBeams1[i].position.x+=((int)my_center_x/40 + 1)*40 + (rand()%3 + 1) * 16.0f - 7.0f;   
                fireBeams2[i].position.x=fireBeams1[i].position.x -6.5f;   
                beam1[i].position.x=fireBeams1[i].position.x + 1.3f - 8.0f;   
            }
            if(my_center_y > boomerang1[i].position.y)
            {
                boomerang1[i].position.x = ((int)my_center_x/40 + 1)*40 + (rand()%3 + 1) * 16.0f;
                boomerang1[i].position.y = rand()%3 + 1.0f;
            }
            if(my_center_x - fireLines1[i].position.x > 5.0f)
            {
                fireLines1[i].position.x+=40.0f;
                fireLines1[i].position2.x+=40.0f;
            }
        }
    }
}*/

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    seg = Segmentdisplay();
    ball1       = Ball(0.0f, 0.0f, COLOR_BLACK);
    platform1   = Platform(COLOR_GREEN);
    magnet1 = Magnet(my_center_x + 4.0f,my_center_y + 3.0f, COLOR_MAGENTA);
    for(int i=0;i<100;i++)
    {
        coins1[i]       = Coins(i/4,COLOR_RED);
    }
    for(int i=0;i<100;i++)
        coins2[i]       = Coins(i/4,COLOR_NAVY);
    power1 = Power(1, COLOR_GOLD);
    power2 = Power(3, COLOR_SKY_BLUE);
    power3 = Power(3, COLOR_CRIMSON);

    for(int i=0;i<12;i++)
    {
        boomerang1[i] = Boomerang(COLOR_PURPLE);
        fireBeams1[i] = FireBeams(COLOR_SLATE_GRAY);
        fireBeams2[i] = FireBeams2(fireBeams1[i].position.x - 7.0f, fireBeams1[i].position.y, COLOR_SLATE_GRAY);
        beam1[i] = Beam(fireBeams1[i].position.x + 1.3f - 8.0f, fireBeams1[i].position.y, COLOR_YELLOW);
        fireLines1[i] = FireLines(COLOR_RED);
    }
    background1 = Background(COLOR_BLUE);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void check(GLFWwindow *window){

    //With coins
    int flag =1;
    //cout << "Score=" << score << endl;
    for(int i=0;i<100;i++)
    {
        if(detect_collision(ball1.bounding_box(),coins2[i].bounding_box()))
        {
            //std::cout << "Ball:" << ball1.position.x << " " << ball1.position.y << std::endl;
            //std::cout << coins1[i].position.x << " " << coins1[i].position.y << std::endl;
            coins2[i].position.x+=40.0f;
            //cout << "Collected" << endl;
            //break;
            if(flag)
                score+=20;
            flag =0;
        }
    }
    for(int i=0;i<100;i++)
    {
        if(detect_collision(ball1.bounding_box(),coins1[i].bounding_box()))
        {
            //std::cout << "Ball:" << ball1.position.x << " " << ball1.position.y << std::endl;
            //std::cout << coins1[i].position.x << " " << coins1[i].position.y << std::endl;
            coins1[i].position.x+=40.0f;
            //cout << "Collected" << endl;
            //break;
            if(flag)
                score+=10;
            flag =0;
        }  
    }

    //With Power Ups
    if(detect_collision(ball1.bounding_box(),power1.bounding_box()))
    {
        score+=100;
        power1.position.x+=40.0f;
    }

    if(detect_collision(ball1.bounding_box(),power2.bounding_box()))
    {
        health=100;
        power2.position.x+=40.0f;
    }

    //With beams
    for(int i=0;i<12;i++)
    {
        //if(detect_collision(ball1.bounding_box(),fireBeams1[i].bounding_box()) || detect_collision(ball1.bounding_box(),fireBeams2[i].bounding_box()) || (detect_collision(ball1.bounding_box(),beam1[i].bounding_box()) && beamOn[i])) 
        if((detect_collision(ball1.bounding_box(),beam1[i].bounding_box()) && beamOn[i])) 
        {
            //cout << ball1.position.x << " " << ball1.position.y << endl;
            //cout << fireBeams2[i].position.x << " " << fireBeams2[i].position.y << endl;
            if(beam1[i].damage)
            {
                beam1[i].damage=0;
                health-=10;
            }
        }
    }

    //With Fire Lines
    for(int i=0;i<12;i++)
    {
        float dist=(ball1.position.x + ball1.position.y - fireLines1[i].position.x - fireLines1[i].position.y - 6.0f)/sqrt(2);
        if(abs(dist) < 0.1f && calc(ball1.position.x,ball1.position.y,fireLines1[i].position.x,fireLines1[i].position.y)<6.4f && calc(ball1.position.x,ball1.position.y,fireLines1[i].position2.x,fireLines1[i].position2.y)<6.4f)
        {
            //cout << ball1.position.x << " " << ball1.position.y << endl;
            if(fireLines1[i].damage)
            {
                fireLines1[i].damage=0;
                health-=10;
            }
        }
    }

    //With Boomerangs
    for(int i=0;i<12;i++)
    {
        if((detect_collision(ball1.bounding_box(),boomerang1[i].bounding_box())))
        {
            if(boomerang1[i].damage)
            {
                boomerang1[i].damage=0;
                health-=20;
            }

        }
    }

    //Power ball
    if(shot)
    {
    for(int i=0;i<12;i++)
    {
        float dist=(power3.position.x + power3.position.y - fireLines1[i].position.x - fireLines1[i].position.y +1.0f)/sqrt(2);
        
        if((detect_collision(power3.bounding_box(),beam1[i].bounding_box()) && beamOn[i]))
        {
            shot=0;
            fireBeams1[i].position.x=-40.0f;   
            fireBeams2[i].position.x=fireBeams1[i].position.x -6.5f;   
            beam1[i].position.x=fireBeams1[i].position.x + 1.3f - 8.0f;   
        }
        else if(abs(dist) < 0.1f && calc(power3.position.x-0.5f,power3.position.y-0.5f,fireLines1[i].position.x,fireLines1[i].position.y)<6.4f && calc(power3.position.x-0.5f,power3.position.y-0.5f,fireLines1[i].position2.x,fireLines1[i].position2.y)<6.4f)
        {
            shot=0;
            fireLines1[i].position.x=-40.0f;
            fireLines1[i].position2.x=-40.0f;
        }
        else if((detect_collision(power3.bounding_box(),boomerang1[i].bounding_box())))
        {
            shot=0;
            boomerang1[i].position.x=-40.0f;
        }
    }
    }
}

float calc(float a, float b, float x, float y)
{
    a-=0.75f;
    b+=0.75f;
    return (float)sqrt((a-x)*(a-x) + (b-y)*(b-y));
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            //tick_elements();
            tick_input(window);
            player_checks();
            //cout << ball1.position[1] << endl;
        	update_positions();
            check(window);
        }	
        if(health<=0)
            quit(window);
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
