#include "main.h"

#ifndef ELON_SQ_PYRID_H
#define ELON_SQ_PYRID_H


class Elon_Sq_Pyrid {
public:
    Elon_Sq_Pyrid() {}
    Elon_Sq_Pyrid(float x, float y);
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
