#include "main.h"
#include "coins.h"

Coins::Coins(int start, color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    Coins::bounding_box();
    GLfloat vertex_buffer_data[9*4];
        float x = (rand()%10)*16 + rand() % 8;
        float y = (rand() % 10) + 0.1f -1.0f;
        //std::cout << x << " " << y << std::endl;
        //std::cout << y << std::endl;
        Coins::set_position(x,y);
        vertex_buffer_data[0] = 0;
        vertex_buffer_data[ + 1] = 0;
        vertex_buffer_data[ + 2] = 0.0f;
        vertex_buffer_data[ + 3] = 0;
        vertex_buffer_data[ + 4] = 0 + 0.1f;
        vertex_buffer_data[ + 5] = 0.0f;
        vertex_buffer_data[ + 6] = 0+0.1f;
        vertex_buffer_data[ + 7] = 0 ;
        vertex_buffer_data[ + 8] = 0.0f;
        vertex_buffer_data[ + 9] = 0;
        vertex_buffer_data[ + 10] = 0;
        vertex_buffer_data[ + 11] = 0.0f;
        vertex_buffer_data[ + 12] = 0;
        vertex_buffer_data[ + 13] = 0 + 0.1f;
        vertex_buffer_data[ + 14] = 0.0f;
        vertex_buffer_data[ + 15] = 0 - 0.1f;
        vertex_buffer_data[ + 16] = 0;
        vertex_buffer_data[ + 17] = 0.0f;
        vertex_buffer_data[ + 18] = 0;
        vertex_buffer_data[ + 19] = 0;
        vertex_buffer_data[ + 20] = 0.0f;
        vertex_buffer_data[ + 21] = 0 - 0.1f;
        vertex_buffer_data[ + 22] = 0;
        vertex_buffer_data[ + 23] = 0.0f;
        vertex_buffer_data[ + 24] = 0;
        vertex_buffer_data[ + 25] = 0 - 0.1f;
        vertex_buffer_data[ + 26] = 0.0f;
        vertex_buffer_data[ + 27] = 0;
        vertex_buffer_data[ + 28] = 0;
        vertex_buffer_data[ + 29] = 0.0f;
        vertex_buffer_data[ + 30] = 0;
        vertex_buffer_data[ + 31] = 0 - 0.1f;
        vertex_buffer_data[ + 32] = 0.0f;
        vertex_buffer_data[ + 33] = 0 + 0.1f;
        vertex_buffer_data[ + 34] = 0;
        vertex_buffer_data[ + 35] = 0.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->object = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data, color, GL_FILL);
}

void Coins::draw(glm::mat4 VP) {
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

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Coins::bounding_box() {
    bounding_box_t bbox = { this->position.x, this->position.y, 0.2f, 0.2f };
    return bbox;
}