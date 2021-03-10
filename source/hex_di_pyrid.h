#include "main.h"

#ifndef HEX_DI_PYRID_H
#define HEX_DI_PYRID_H


class Hex_Di_Pyrid {
public:
    Hex_Di_Pyrid() {}
    Hex_Di_Pyrid(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif
