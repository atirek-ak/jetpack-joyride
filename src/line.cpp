#include "line.h"
#include "main.h"

Line::Line(float fx, float fy, float tx, float ty)
{
    if (tx == fx) rotation = ty > fy ? M_PI/2 : -M_PI/2;
    else if (ty == fy) rotation = tx > fx ? 0 : M_PI;
    else rotation = atan((ty-fy)/(tx-fx));
    position = glm::vec3(fx, fy, 0);
    static const GLfloat vertex_buffer_data [] = {
        0, 0, 0,
        0.2, 0, 0
    };
    this->object = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}


void Line::draw(glm::mat4 VP) {
    if (!this->object) return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(rotation, glm::vec3(0,0,1));
    glm::mat4 translate = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
