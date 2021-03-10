#include "main.h"
#include "timer.h"
#include "hex_di_pyrid.h"
#include "penta_anti_prism.h"
#include "elon_sq_pyrid.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

int ch;
/**************************
* Customizable functions *
**************************/

// Ball ball1;
Hex_Di_Pyrid hex_di_pyrid1;
Penta_anti_Prism penta_anti_prism1;
Elon_Sq_Pyrid elon_sq_pyrid1;
// Penta_Anti_Prism

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
    glm::vec3 eye(5 * cos(camera_rotation_angle * M_PI / 180.0f), 0, 5 * sin(camera_rotation_angle * M_PI / 180.0f));
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
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
    if (ch == 1)
        hex_di_pyrid1.draw(VP);
    if (ch == 2)
        penta_anti_prism1.draw(VP);
    if (ch == 3)
        elon_sq_pyrid1.draw(VP);
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
    if (ch == 1)
    {
        if (left)
            hex_di_pyrid1.rotatX += 1;
        if (right)
            hex_di_pyrid1.rotatX -= 1;
        if (up)
            hex_di_pyrid1.rotatY += 1;
        if (down)
            hex_di_pyrid1.rotatY -= 1;
        if (dot)
            hex_di_pyrid1.rotatZ += 1;
        if (slash)
            hex_di_pyrid1.rotatZ -= 1;
    }
    if (ch == 2)
    {
        if (left)
            penta_anti_prism1.rotatX += 1;
        if (right)
            penta_anti_prism1.rotatX -= 1;
        if (up)
            penta_anti_prism1.rotatY += 1;
        if (down)
            penta_anti_prism1.rotatY -= 1;
        if (dot)
            penta_anti_prism1.rotatZ += 1;
        if (slash)
            penta_anti_prism1.rotatZ -= 1;
    }
    if (ch == 3)
    {
        if (left)
            elon_sq_pyrid1.rotatX += 1;
        if (right)
            elon_sq_pyrid1.rotatX -= 1;
        if (up)
            elon_sq_pyrid1.rotatY += 1;
        if (down)
            elon_sq_pyrid1.rotatY -= 1;
        if (dot)
            elon_sq_pyrid1.rotatZ += 1;
        if (slash)
            elon_sq_pyrid1.rotatZ -= 1;
        if (w)
            elon_sq_pyrid1.posY += 0.1;
        if (s)
            elon_sq_pyrid1.posY -= 0.1;
        if (a)
            elon_sq_pyrid1.posZ += 0.1;
        if (d)
            elon_sq_pyrid1.posZ -= 0.1;
        if (e)
            elon_sq_pyrid1.posX += 0.1;
        if (r)
            elon_sq_pyrid1.posX -= 0.1;
    }
}

void tick_elements()
{
    // ball1.tick();
    if (ch == 1)
        hex_di_pyrid1.tick();
    if (ch == 2)
        penta_anti_prism1.tick();
    if (ch == 3)
        elon_sq_pyrid1.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // ball1 = Ball(0, 0, colorBuffer);
    if (ch == 1)
        hex_di_pyrid1 = Hex_Di_Pyrid(0, 0);
    if (ch == 2)
        penta_anti_prism1 = Penta_anti_Prism(0, 0);
    if (ch == 3)
        elon_sq_pyrid1 = Elon_Sq_Pyrid(0, 0);

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
