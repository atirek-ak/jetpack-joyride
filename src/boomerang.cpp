#include "main.h"
#include "boomerang.h"

Boomerang::Boomerang (color_t color) {
    this->rotation = 0.0f;
    this->speed=0;
    this->time=0;
    this->damage=1;
        float x =  (rand()%10 + 1) * 16.0f;
        float y = rand()%3 + 1.0f;
        Boomerang::set_position(x,y);
        float angle = 0.0f;
    float rot_angle = (3.14159265359)/100;

    GLfloat vertex_buffer_data[18];
    vertex_buffer_data[0] = -0.5f;
    vertex_buffer_data[1] =  0.0f;
    vertex_buffer_data[2] =  0.0f;

    vertex_buffer_data[3] =  0.0f;
    vertex_buffer_data[4] =   0.0f;
    vertex_buffer_data[5] =  0.0f;

    vertex_buffer_data[6] =   0.5f;
    vertex_buffer_data[7] =   0.5f;
    vertex_buffer_data[8] =   0.0f;

    vertex_buffer_data[9] =  -0.5f;
    vertex_buffer_data[10] =  0.0f;
    vertex_buffer_data[11] =  0.0f;

    vertex_buffer_data[12] =   0.0f;
    vertex_buffer_data[13] =   0.0f;
    vertex_buffer_data[14] =   0.0f;

    vertex_buffer_data[15] =   0.5f;
    vertex_buffer_data[16] =  -0.5f;
    vertex_buffer_data[17] =   0.0f;

    

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
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

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Boomerang::bounding_box() {
    bounding_box_t bbox = { this->position.x , this->position.y , 1.0f , 0.5f };
    return bbox;
}