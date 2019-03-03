#include "main.h"
#include "background.h"

Background::Background(color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    int n=100;
    float y=0.5f, x=-4.0f;
    GLfloat vertex_buffer_data[n*18];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[i*18] = x;
        vertex_buffer_data[i*18 + 1] = y;
        vertex_buffer_data[i*18 + 2] = 0.0f;

        vertex_buffer_data[i*18 + 3] = x;
        vertex_buffer_data[i*18 + 4] = y +3.5f;
        vertex_buffer_data[i*18 + 5] = 0.0f;

        vertex_buffer_data[i*18 + 6] = x + 4.0f;
        vertex_buffer_data[i*18 + 7] = y;
        vertex_buffer_data[i*18 + 8] = 0.0f;

        vertex_buffer_data[i*18 + 9] = x;
        vertex_buffer_data[i*18 + 10] = y +3.5f;
        vertex_buffer_data[i*18 + 11] = 0.0f;

        vertex_buffer_data[i*18 + 12] = x + 4.0f;
        vertex_buffer_data[i*18 + 13] = y;
        vertex_buffer_data[i*18 + 14] = 0.0f;
        
        vertex_buffer_data[i*18 + 15] = x + 4.0f;
        vertex_buffer_data[i*18 + 16] = y + 3.5f;
        vertex_buffer_data[i*18 + 17] = 0.0f;

        x+=4.0f;
        y= -2.5f - y;
    }
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->object = create3DObject(GL_TRIANGLES, 2*n*3, vertex_buffer_data, color, GL_FILL);
}

void Background::draw(glm::mat4 VP) {
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

void Background::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}