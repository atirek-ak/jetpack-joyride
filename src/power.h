#include "main.h"

#ifndef POWER_H
#define POWER_H


class Power {
public:
    Power() {}
    Power(int y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 
