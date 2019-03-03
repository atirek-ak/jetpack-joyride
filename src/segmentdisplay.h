#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include "digit.h"

class Segmentdisplay
{
public:
    Segmentdisplay();
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void update(int score);
    void add(int d = 2);
    void subtract(int d = 1);
    int view();
    void reset();
    void set_position(float a, float b);

private:
    int score, digslen;
    Digit digs[50];
};

#endif // SCORE_H
