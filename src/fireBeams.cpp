#include "main.h"
#include "fireBeams.h"

FireBeams::FireBeams (color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = -90.0f;
    this->speed=0;
    this->time=0;
    FireBeams::bounding_box();
        float x =  (rand()%10 + 1) * 16.0f - 7.0f;
        float y = rand()%3 - 1.0f;
        FireBeams::set_position(x,y);
        float angle = 0.0f;
    float rot_angle = (3.14159265359)/100;

    GLfloat vertex_buffer_data[100*9];
    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i] = 0.0;
        vertex_buffer_data[9*i+1] = 0.0 - 1.5f;
        vertex_buffer_data[9*i+2] = 0;

        vertex_buffer_data[9*i+3] = 0.5*cos(angle);
        vertex_buffer_data[9*i+4] = 0.5*sin(angle) - 1.5f;
        vertex_buffer_data[9*i+5] = 0;

        vertex_buffer_data[9*i+6] = 0.5*cos(angle+rot_angle);
        vertex_buffer_data[9*i+7] = 0.5*sin(angle+rot_angle) - 1.5f;
        vertex_buffer_data[9*i+8] = 0;

        angle+=rot_angle;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*100, vertex_buffer_data, color, GL_FILL);
}

void FireBeams::draw(glm::mat4 VP) {
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

void FireBeams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t FireBeams::bounding_box() {
    bounding_box_t bbox = { this->position.x + 0.17f - 4.5f, this->position.y + 0.3f, 0.25f, 0.5f };
    return bbox;
}


///Fire Beams 2

FireBeams2::FireBeams2 (float a, float b, color_t color) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 90.0f;
    this->speed=0;
    this->time=0;
    FireBeams2::bounding_box();
        float x =  a;
        float y =  b;
        FireBeams2::set_position(x + 0.5f,y);
        float angle = 0.0f;
    float rot_angle = (3.14159265359)/100;

    GLfloat vertex_buffer_data[100*9];
    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i] = 0.0;
        vertex_buffer_data[9*i+1] = 0.0 + 2.0f;
        vertex_buffer_data[9*i+2] = 0;

        vertex_buffer_data[9*i+3] = 0.5*cos(angle);
        vertex_buffer_data[9*i+4] = 0.5*sin(angle) + 2.0f;
        vertex_buffer_data[9*i+5] = 0;

        vertex_buffer_data[9*i+6] = 0.5*cos(angle+rot_angle);
        vertex_buffer_data[9*i+7] = 0.5*sin(angle+rot_angle) + 2.0f;
        vertex_buffer_data[9*i+8] = 0;

        angle+=rot_angle;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*100, vertex_buffer_data, color, GL_FILL);
}

void FireBeams2::draw(glm::mat4 VP) {
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

void FireBeams2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t FireBeams2::bounding_box() {
    bounding_box_t bbox = { this->position.x + 0.17f, this->position.y + 0.3f, 0.25f, 0.5f };
    return bbox;
}


//The beam

Beam::Beam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->damage=1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -3.0f + 3.0f, -3.5f + 3.5f,0.0f, // triangle 1 : begin
        -3.0f + 3.0f, -3.0f + 3.5f,0.0f,
         4.0f + 3.0f, -3.0f + 3.5f,0.0f, // triangle 1 : end
        -3.0f + 3.0f, -3.5f + 3.5f,0.0f, // triangle 1 : begin
         4.0f + 3.0f, -3.0f + 3.5f,0.0f,
         4.0f + 3.0f, -3.5f + 3.5f,0.0f// triangle 1 : end

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Beam::draw(glm::mat4 VP) {
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

void Beam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Beam::bounding_box() {
    bounding_box_t bbox = { this->position.x + 3.5f, this->position.y + 0.3f, 7.0f, 0.5f };
    return bbox;
}