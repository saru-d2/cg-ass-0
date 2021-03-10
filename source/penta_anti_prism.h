#include "main.h"

#ifndef PENTA_ANTI_PRISM_H
#define PENTA_ANTI_PRISM_H


class Penta_anti_Prism {
public:
    Penta_anti_Prism() {}
    Penta_anti_Prism(float x, float y);
    glm::vec3 position;
    float rotation;
    float rotatY;
    float rotatX;
    float rotatZ;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif
