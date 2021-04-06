#include "main.h"
#include "timer.h"

#include "shape.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

float cameraX = -5;
float cameraY = 0;
float cameraZ = 0;

float cameraLookX = 5;
float cameraLookY = 0;
float cameraLookZ = 0;
glm::vec3 cameraUp(0, 1, 0);

// bool changeShape = false;

int ch;
/**************************
* Customizable functions *
**************************/

// Ball ball1;
Shape shape1;
// Penta_Anti_Prism
// int cntr = 0;
void rotateCameraAboutObject(float rotatAdd)
{
    // cntr++;
    // float currAngle = atan( (shape1.posY - cameraY) / (shape1.posX - cameraX));
    // currAngle += rotatAdd;
    // float currDistAlongXY = sqrt(pow(shape1.posX - cameraX, 2) + pow(shape1.posY - cameraY, 2));
    // cameraX = currDistAlongXY * cos(currAngle);
    // cameraY = currDistAlongXY * sin(currAngle);
    // if (currAngle >= M_PI) cameraX *= -1;
    // if (currAngle >= M_PI) cameraY *= -1;
    glm::vec3 look(shape1.posX - cameraX, shape1.posY - cameraY, shape1.posZ - cameraZ);
    glm::vec3 direction = glm::normalize(glm::cross(look, cameraUp));
    cameraX += direction[0] * rotatAdd;
    cameraY += direction[1] * rotatAdd;
    cameraZ += direction[2] * rotatAdd;
    cameraLookX = shape1.posX - cameraX;
    cameraLookY = shape1.posY - cameraY;
    cameraLookZ = shape1.posZ - cameraZ;
    // std::cout << currAngle << ',' << std::endl;

    // std::cout << cameraLookX << "," << cameraLookY << "," << cameraLookZ << std::endl;
    // std::cout << cameraX << "," << cameraY << "," << cameraZ << std::endl;
}

void teleport_camera(int ch)
{
    cameraX = 0;
    cameraY = 0;
    cameraZ = 0;
    if (ch == 0)
        cameraX = 5;
    if (ch == 1)
        cameraX = -5;
        cameraZ = -5;
    if (ch == 2)
        cameraZ = 5;
    // std::cout << cameraX << "," << cameraY << "," << cameraZ << " " << cameraLookX << "," << cameraLookY << "," << cameraLookZ << " "<<shape1.posX<<","<<shape1.posY<<","<<shape1.posZ<<std::endl;
    cameraLookX = shape1.posX - cameraX;
    cameraLookY = shape1.posY - cameraY;
    cameraLookZ = shape1.posZ - cameraZ;
}

void genNextShape(){
    ch++;
    if (ch == 4) ch = 1;
    shape1 = Shape(ch);
}

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(cameraX, cameraY, cameraZ);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(0, 0, 0);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, eye + glm::vec3(cameraLookX, cameraLookY, cameraLookZ), up); // Rotating Camera for 3D
    // Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    shape1.draw(VP);
}

void tick_input(GLFWwindow *window)
{
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int dot = glfwGetKey(window, GLFW_KEY_PERIOD);
    int slash = glfwGetKey(window, GLFW_KEY_SLASH);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int r = glfwGetKey(window, GLFW_KEY_R);
    int h = glfwGetKey(window, GLFW_KEY_H);
    int j = glfwGetKey(window, GLFW_KEY_J);
    int k = glfwGetKey(window, GLFW_KEY_K);
    int l = glfwGetKey(window, GLFW_KEY_L);
    int n = glfwGetKey(window, GLFW_KEY_N);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int u = glfwGetKey(window, GLFW_KEY_U);
    int i = glfwGetKey(window, GLFW_KEY_I);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int v = glfwGetKey(window, GLFW_KEY_V);
    // int g = glfwGetKey(window, GLFW_KEY_G);
    

    if (left)
        shape1.rotatX += 1;
    if (right)
        shape1.rotatX -= 1;
    if (up)
        shape1.rotatY += 1;
    if (down)
        shape1.rotatY -= 1;
    if (dot)
        shape1.rotatZ += 1;
    if (slash)
        shape1.rotatZ -= 1;
    if (w)
        shape1.posY += 0.1;
    if (s)
        shape1.posY -= 0.1;
    if (a)
        shape1.posZ += 0.1;
    if (d)
        shape1.posZ -= 0.1;
    if (e)
        shape1.posX += 0.1;
    if (r)
        shape1.posX -= 0.1;
    if (h)
        cameraX += 0.1;
    if (j)
        cameraX -= 0.1;
    if (k)
        cameraY += 0.1;
    if (l)
        cameraY -= 0.1;
    if (n)
        cameraZ += 0.1;
    if (m)
        cameraZ -= 0.1;
    if (u)
        rotateCameraAboutObject(0.1);
    if (i)
        rotateCameraAboutObject(-0.1);
    if (x)
        teleport_camera(0);
    if (c)
        teleport_camera(1);
    if (v)
        teleport_camera(2);
    if (changeShape)
        genNextShape();
        changeShape = false;
}

void tick_elements()
{
    // ball1.tick();
    shape1.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // ball1 = Ball(0, 0, colorBuffer);
    shape1 = Shape(ch);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/vert.glsl", "../source/shaders/frag.glsl");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    cout << "1: hexa Bi.. 2: Penta anti.. 3: Elon Sq Pyr" << endl;
    cin >> ch;
    cout << ch << endl;
    srand(time(0));
    int width = 600;
    int height = 600;

    std::cout << "hello" << endl;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
