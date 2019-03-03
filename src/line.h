#ifndef LINE_H
#define LINE_H

#include "main.h"

class Line
{
public:
    Line() {}
    Line(float fx, float fy, float tx, float ty);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO* object = NULL;
};

#endif // LINE_H
