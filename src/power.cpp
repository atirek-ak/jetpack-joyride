#include "main.h"
#include "power.h"

Power::Power(int start, color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speed=0;
    Power::bounding_box();
        float x =  ((start + 1.0f)/2.0f)*(rand()%3 + 1) * 16.0f + 8.0f;
        float y = start * 1.0f;
        Power::set_position(x,y);
        float angle = 0;
    float rot_angle = (2*3.14159265359)/100;

    GLfloat vertex_buffer_data[100*9];
    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i] = 0.0;
        vertex_buffer_data[9*i+1] = 0.0;
        vertex_buffer_data[9*i+2] = 0;

        vertex_buffer_data[9*i+3] = 0.5*cos(angle);
        vertex_buffer_data[9*i+4] = 0.5*sin(angle);
        vertex_buffer_data[9*i+5] = 0;

        vertex_buffer_data[9*i+6] = 0.5*cos(angle+rot_angle);
        vertex_buffer_data[9*i+7] = 0.5*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8] = 0;

        angle+=rot_angle;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*100, vertex_buffer_data, color, GL_FILL);
}

void Power::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Power::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Power::bounding_box() {
    bounding_box_t bbox = { this->position.x, this->position.y, 1.0f, 1.0f };
    return bbox;
}