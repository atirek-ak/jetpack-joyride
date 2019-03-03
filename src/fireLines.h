#include "main.h"

#ifndef FIRELINES_H
#define FIRELINES_H


class FireLines {
public:
    FireLines() {}
    FireLines(color_t color);
    glm::vec3 position;
    glm::vec3 position2;
    int time;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int damage;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 