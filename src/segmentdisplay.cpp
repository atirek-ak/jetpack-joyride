#include "segmentdisplay.h"
#include "main.h"
#include <cstring>

Segmentdisplay::Segmentdisplay()
{
    score = 0;
    digslen = 0;
    position.x = 0;
    position.y = 3.5;
}

void Segmentdisplay::update(int score) {
    this->score = score;
    char scorestr[50];
    sprintf(scorestr, "%d", score);
    digslen = strlen(scorestr);
    for (int i = digslen - 1; i >= 0; i--) {
        digs[i] = Digit(scorestr[i], 4 - 0.3*(digslen - i) + position.x, position.y);
    }
}

void Segmentdisplay::add(int d) {
    update(score+d);
}

void Segmentdisplay::subtract(int d) {
    update(score-d);
}

int Segmentdisplay::view() {
    return score;
}

void Segmentdisplay::reset(){
    score =0;
}

void Segmentdisplay::draw(glm::mat4 VP) {
    for (int i = 0; i < digslen; i++) digs[i].draw(VP);
}

void Segmentdisplay::set_position(float x, float y){
    this->position = glm::vec3(x, y, 0);
}
