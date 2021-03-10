#include "main.h"

#ifndef SHAPE_H
#define SHAPE_H


class Shape {
public:
    Shape() {}
    Shape(int ch);
    glm::vec3 position;
    float rotation;
    float rotatY;
    float rotatX;
    float rotatZ;

    float posX;
    float posY;
    float posZ;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif
