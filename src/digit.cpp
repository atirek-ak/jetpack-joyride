#include "digit.h"
#include "main.h"

Digit::Digit(char c, float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    bool l[8];
    for (int i = 0; i < 8; i++) l[i] = false;
    switch (c) {
    case '0':
        l[1] = l[2] = l[3] = l[4] = l[5] = l[6] = true;
        break;
    case '1':
        l[2] = l[3] = true;
        break;
    case '2':
        l[1] = l[2] = l[7] = l[5] = l[4] = true;
        break;
    case '3':
        l[1] = l[2] = l[7] = l[3] = l[4] = true;
        break;
    case '4':
        l[6] = l[7] = l[2] = l[3] = true;
        break;
    case '5':
        l[1] = l[6] = l[7] = l[3] = l[4] = true;
        break;
    case '6':
        l[1] = l[6] = l[7] = l[3] = l[4] = l[5] = true;
        break;
    case '7':
        l[1] = l[2] = l[3] = true;
        break;
    case '8':
        l[1] = l[2] = l[7] = l[5] = l[4] = l[3] = l[6] = true;
        break;
    case '9':
        l[1] = l[2] = l[7] = l[4] = l[3] = l[6] = true;
        break;
    case '-':
        l[7] = true;
    }
    const GLfloat vbl[][6] = {
        {0, 0.4, 0, 0.2, 0.4, 0},
        {0.2, 0.4, 0, 0.2, 0.2, 0},
        {0.2, 0.2, 0, 0.2, 0, 0},
        {0.2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0.2, 0},
        {0, 0.4, 0, 0, 0.2, 0},
        {0, 0.2, 0, 0.2, 0.2, 0},
    };
    for (int i = 0; i < 7; i++) {
        if (!l[i+1]) continue;
        lines[i] = Line(x+vbl[i][0], y+vbl[i][1], x+vbl[i][3], y+vbl[i][4]);
    }
}

void Digit::draw(glm::mat4 VP) {
    for (int i = 0; i < 7; i++) lines[i].draw(VP);
}
