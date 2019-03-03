#include "main.h"

#ifndef FIREBEAMS_H
#define FIREBEAMS_H


class FireBeams {
public:
    FireBeams() {}
    FireBeams(color_t color);
    glm::vec3 position;
    int time;
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

//Fire Beams 2

#ifndef FIREBEAMS2_H
#define FIREBEAMS2_H


class FireBeams2 {
public:
    FireBeams2() {}
    FireBeams2(float x, float y,color_t color);
    glm::vec3 position;
    int time;
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

//The Beam


#ifndef BEAM_H
#define BEAM_H


class Beam {
public:
    Beam() {}
    Beam(float x, float y, color_t color);
    glm::vec3 position;
    int damage;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif