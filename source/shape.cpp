#include "shape.h"
#include "main.h"
#include <cmath>

// float sqrt3by2 = sqrt(3) / 2.0;
// float half = 0.5

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

Shape::Shape(int ch)
{
    std::cout << "helloooooooo" << std::endl;
    float half = 0.5;
    float sqrt3by2 = sqrt(3) / 2.0;

    int numTriangles = 16;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->rotatX = 0;
    this->rotatY = 0;
    this->rotatZ = 0;

    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    speed = 1;

    // {x, y, z}

    if (ch == 3)
    {
        //elon_sq_pyrid
        GLfloat vertGuide[10][3] = {
            {0.0f, 0.0f, 2.0f},    //0
            {1.0f, -1.0f, 1.0f},   //1
            {-1.0f, -1.0f, 1.0f},  //2
            {-1.0f, 1.0f, 1.0f},   //3
            {1.0f, 1.0f, 1.0f},    //4
            {1.0f, -1.0f, -1.0f},  //5
            {-1.0f, -1.0f, -1.0f}, //6
            {-1.0f, 1.0f, -1.0f},  //7
            {1.0f, 1.0f, -1.0f},   //8
            {0.0f, 0.0f, -2.0f},   //9
        };
        int triangleList[16][3] = {
            // top triangle faces
            {0, 1, 2}, //0
            {0, 1, 4}, //0
            {0, 4, 3}, //0
            {0, 3, 2}, //0
            //bottom triangle faces
            {9, 5, 8}, //0
            {9, 5, 6}, //0
            {9, 7, 6}, //0
            {9, 7, 8}, //0
            //squ sides
            {1, 4, 5}, //0
            {4, 5, 8}, //0

            {2, 5, 1}, //0
            {2, 5, 6}, //0

            {3, 6, 2}, //0
            {3, 6, 7}, //0

            {3, 8, 4}, //0
            {3, 8, 7}, //0
        };
        GLfloat vertex_buffer_data[9 * numTriangles];
        std::cout << "hi" << std::endl;
        for (int i = 0; i < numTriangles; i++)
        {
            // for each triangle
            for (int j = 0; j < 3; j++)
            {
                // for each pt in each triangle
                for (int k = 0; k < 3; k++)
                {
                    std::cout << "hi"
                              << " " << i << "," << j << std::endl;
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
    }
    this->object = create3DObject(GL_TRIANGLES, numTriangles * 3, vertex_buffer_data, colorBuffer, GL_FILL);
}

void Shape::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(glm::vec3(this->posX, this->posY, this->posZ)); // glTranslatef
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

void Shape::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Elon_Sq_Pyrid::tick()
{
    // this->rotatX += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}