#include "ball.h"
#include "main.h"

//Player
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    //std::cout << "Ball:" << x << " " << y << std::endl;
    this->rotation = 0;
    speed = 0;
    Ball::bounding_box();
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
          -4.00f, -3.00f, 0.0f, // triangle 1 : begin
          -4.00f, -2.75f, 0.0f,
          -3.90f, -2.75f, 0.0f, 
          -4.00f, -3.00f, 0.0f, // triangle 1 : begin
          -3.90f, -3.00f, 0.0f,
          -3.90f, -2.75f, 0.0f,
          -3.85f, -3.00f, 0.0f, // triangle 1 : begin
          -3.85f, -2.75f, 0.0f,
          -3.75f, -2.75f, 0.0f,
          -3.85f, -3.00f, 0.0f, // triangle 1 : begin
          -3.75f, -3.00f, 0.0f,
          -3.75f, -2.75f, 0.0f,
          -4.00f, -2.75f, 0.0f, // triangle 1 : begin
          -4.00f, -2.25f, 0.0f,
          -3.75f, -2.25f, 0.0f,
          -4.00f, -2.75f, 0.0f, // triangle 1 : begin
          -3.75f, -2.75f, 0.0f,
          -3.75f, -2.25f, 0.0f    
     };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->rotation += 0;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Ball::bounding_box() {
    bounding_box_t bbox = { this->position.x - 4.0 + 0.125f, this->position.y - 3.0 + 0.375f, 0.25f, 0.75f };
    //std::cout << "Called" << std::endl;
    return bbox;
}
