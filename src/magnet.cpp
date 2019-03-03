#include "main.h"
#include "magnet.h"

Magnet::Magnet (float a, float b,color_t color) {
    this->rotation = -90.0f;
    this->speed=0;
    this->time=0;
    this->damage=1;
        float x = a;
        float y = b;
        Magnet::set_position(x,y);
        float angle = 0.0f;
    float rot_angle = (3.14159265359)/100;

    GLfloat vertex_buffer_data[100*9 +18];
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
    vertex_buffer_data[900] = 0.0f;
    vertex_buffer_data[901] = 0.0f;
    vertex_buffer_data[902] = 0.0f;

    vertex_buffer_data[903] = 0.5f;
    vertex_buffer_data[904] = 0.0f;
    vertex_buffer_data[905] = 0.0f;

    vertex_buffer_data[906] = 0.5f;
    vertex_buffer_data[907] = -0.5f;
    vertex_buffer_data[908] = 0.0f;

    vertex_buffer_data[909] = 0.0f;
    vertex_buffer_data[910] = 0.0f;
    vertex_buffer_data[911] = 0.0f;

    vertex_buffer_data[912] = -0.5f;
    vertex_buffer_data[913] = 0.0f;
    vertex_buffer_data[914] = 0.0f;

    vertex_buffer_data[915] = -0.5f;
    vertex_buffer_data[916] = -0.5f;
    vertex_buffer_data[917] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 306, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Magnet::bounding_box() {
    bounding_box_t bbox = { this->position.x , this->position.y , 1.0f , 0.5f };
    return bbox;
}