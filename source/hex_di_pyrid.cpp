#include "hex_di_pyrid.h"
#include "main.h"
#include <cmath>

float sqrt3by2 = sqrt(3) / 2.0;

int numTriangles = 2;

Hex_Di_Pyrid::Hex_Di_Pyrid(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // x, y, z
    GLfloat vertGuide[8][3] = {
        {0.0f, 0.0f, 1.0f},       //0
        {0.0f, 0.0f, -1.0f},      //1
        {0.5f, -sqrt3by2, 0.0f},  //2
        {-0.5f, -sqrt3by2, 0.0f}, //3
        {0.0f, -1.0f, 0.0f},      //4
        {-0.5f, sqrt3by2, 0.0f},  //5
        {0.5f, sqrt3by2, 0.0f},   //6
        {0.0f, 1.0f, 0.0f},       //7
    };
    int triangleList[12][3] = {
        {0, 5, 4}, //1
        {0, 3, 4}, //0
        {0, 5, 6}, //2
        {0, 7, 6}, //3
        {0, 7, 2}, //4
        {0, 3, 2}, //5
        {1, 3, 4}, //6 + 0
        {1, 5, 4}, //6 + 1
        {1, 5, 6}, //6 + 2
        {1, 7, 6}, //6 + 3
        {1, 7, 2}, //6 + 4
        {1, 3, 2}, //6 + 5

        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0
        // {0, 3, 4}, //0

    };
    GLfloat vertex_buffer_data[9 * numTriangles];
    for (int i = 0; i < numTriangles; i++)
    {
        // for each triangle
        for (int j = 0; j < 3; j++)
        {
            // for each pt in each triangle
            for (int k = 0; k < 3; k++)
            {
                vertex_buffer_data[12 * i + 3 * j + k] = vertGuide[triangleList[i][j]][k];
                std::cout << vertGuide[triangleList[i][j]][k] << " ";
                std::cout << "(" << triangleList[i][j] << "," << k << ") ";
            }
            std::cout << "\n";
        }
    }

    

    color_t colors[] = {COLOR_BLACK, COLOR_RED, COLOR_GREEN};

    GLfloat colorBuffer[numTriangles * 3 * 3];

    for (int i = 0; i < numTriangles * 3; i++)
    {
        colorBuffer[3 * i + 0] = (float)colors[i % 3].r / 255.0;
        colorBuffer[3 * i + 1] = (float)colors[i % 3].g / 255.0;
        colorBuffer[3 * i + 2] = (float)colors[i % 3].b / 255.0;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles * 3, vertex_buffer_data, colorBuffer, GL_FILL);
}

void Hex_Di_Pyrid::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Hex_Di_Pyrid::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Hex_Di_Pyrid::tick()
{
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}