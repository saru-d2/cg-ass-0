#include "penta_anti_prism.h"
#include "main.h"
#include <cmath>

const color_t COLOR_0 = {135, 67, 253};
const color_t COLOR_1 = {219, 95, 0};
const color_t COLOR_2 = {80, 4, 84};
const color_t COLOR_3 = {182, 82, 250};
const color_t COLOR_4 = {81, 212, 55};
const color_t COLOR_5 = {0, 240, 202};
const color_t COLOR_6 = {32, 81, 223};
const color_t COLOR_7 = {197, 114, 7};
const color_t COLOR_8 = {105, 159, 4};
const color_t COLOR_9 = {96, 57, 116};
const color_t COLOR_10 = {230, 23, 85};
const color_t COLOR_11 = {43, 74, 90};

const color_t COLOR_ARRAY[] = {
    COLOR_0,
    COLOR_1,
    COLOR_2,
    COLOR_3,
    COLOR_4,
    COLOR_5,
    COLOR_6,
    COLOR_7,
    COLOR_8,
    COLOR_9,
    COLOR_10,
    COLOR_11,
};

Penta_anti_Prism::Penta_anti_Prism(float x, float y)
{
    float half = 0.5;
    float sqrt3by2 = sqrt(3) / 2.0;

    int numTriangles = 16;

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->rotatX = 0;
    this->rotatY = 0;
    this->rotatZ = 0;
    speed = 1;
    // {x, y, z}

    GLfloat vertGuide[10][3] = {
        {-0.95f, -0.31f, 0.5f},  //0
        {-0.59f, 0.81f, 0.5f},   //1
        {0.59f, 0.81f, 0.5f},    //2
        {0.95f, -0.31f, 0.5f},    //3
        {0.0f, -1.0f, 0.5f},     //4
        {-0.59f, -0.81f, -0.5f}, //5
        {-0.95f, 0.31f, -0.5f},  //6
        {0.0f, 1.0f, -0.5f},     //7
        {0.95f, 0.31f, -0.5f},   //8
        {0.59f, -0.81f, -0.5f},  //9

    };
    int triangleList[16][3] = {
        //top face
        {0, 1, 2}, //0
        {0, 2, 3}, //1
        {0, 3, 4}, //2
        //bottom face
        {8, 5, 6}, //3
        {8, 5, 9}, //4
        {8, 6, 7}, //5
        //sides from top
        {0, 1, 6}, //6
        {1, 2, 7}, //7
        {2, 3, 8}, //8
        {3, 4, 9}, //9
        {4, 0, 5}, //10
        //sides from bottom
        {5, 6, 0}, //11
        {6, 7, 1}, //12
        {7, 8, 2}, //13
        {8, 9, 3}, //14
        {9, 5, 4}, //15
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
                vertex_buffer_data[9 * i + 3 * j + k] = vertGuide[triangleList[i][j]][k];
                std::cout << vertGuide[triangleList[i][j]][k] << " ";
                std::cout << "(" << i << "," << j << ", " << triangleList[i][j] << ") ";
                std::flush(std::cout);
            }
            std::cout << std::endl;
        }
    }

    GLfloat colorBuffer[numTriangles * 3 * 3];

    for (int i = 0; i < numTriangles; i++)
    {
        //get triangle ID..
        for (int j = 0; j < 3; j++)
        {
            // for each pt
            colorBuffer[9 * i + 3 * j + 0] = (float)COLOR_ARRAY[triangleList[i][j]].r / 255.0;
            colorBuffer[9 * i + 3 * j + 1] = (float)COLOR_ARRAY[triangleList[i][j]].g / 255.0;
            colorBuffer[9 * i + 3 * j + 2] = (float)COLOR_ARRAY[triangleList[i][j]].b / 255.0;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles * 3, vertex_buffer_data, colorBuffer, GL_FILL);
}

void Penta_anti_Prism::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotatX = glm::rotate((float)(this->rotatX * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatY = glm::rotate((float)(this->rotatY * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatZ = glm::rotate((float)(this->rotatZ * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // glm::mat4 rotate = glm: :rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotatX * rotatY * rotatZ);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Penta_anti_Prism::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Penta_anti_Prism::tick()
{
    // this->rotatX += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}