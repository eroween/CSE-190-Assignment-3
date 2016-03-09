//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2016 Martin-Pierrat Louis (louismartinpierrat@gmail.com)
//


#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#endif
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Mesh.hpp"

Mesh::Mesh(const std::vector<unsigned int> &indices,
        const std::vector<glm::vec3> &vertex_positions) :
    m_datastructure(indices, vertex_positions)
{
    glGenBuffers(1, &this->m_vertex_buffer_id);
    this->update();
}


Mesh::~Mesh()
{
    glDeleteBuffers(1, &this->m_vertex_buffer_id);
}



void
Mesh::debug(int val)
{
    this->m_datastructure.debug(val);
    this->update();
}


void
Mesh::translate(const glm::vec3 &position)
{
    this->m_model = glm::translate(this->m_model, position);
}

void
Mesh::reset()
{
    //this->model = glm::mat4(1.0f);
}

void
Mesh::rotate(float degree, const glm::vec3 &angles)
{
    this->m_model = glm::rotate(this->m_model, degree, angles);
}

void
Mesh::scale(const glm::vec3 &scale)
{
    this->m_model = glm::scale(this->m_model, scale);
}

unsigned int
Mesh::data_size(void) const
{
    return this->m_datastructure.data_size();
}

void
Mesh::bind(unsigned int program_shader_id)
{
    GLint c0 = glGetAttribLocation(program_shader_id, "vertex_position");
    GLint c1 = glGetAttribLocation(program_shader_id, "vertex_color");
    GLint c2 = glGetAttribLocation(program_shader_id, "vertex_normal");

    glEnableVertexAttribArray(c0);
    glEnableVertexAttribArray(c1);
    glEnableVertexAttribArray(c2);

    std::uintptr_t  offset_ptr = 0;
    glVertexAttribPointer(c0, 3, GL_FLOAT, GL_FALSE,
            9 * sizeof(float), (void *)(offset_ptr));
    offset_ptr += 3 * sizeof(float);
    glVertexAttribPointer(c1, 3, GL_FLOAT, GL_FALSE,
            9 * sizeof(float), (void *)(offset_ptr));
    offset_ptr += 3 * sizeof(float);
    glVertexAttribPointer(c2, 3, GL_FLOAT, GL_FALSE,
            9 * sizeof(float), (void *)(offset_ptr));
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_buffer_id);
}

void
Mesh::subdivide(void)
{
    this->m_datastructure.subdivide();
    this->update();
}



const glm::mat4 &
Mesh::model(void) const
{
     return this->m_model;
}

void
Mesh::update(void)
{
    const auto &buffer_data = this->m_datastructure.data();
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_data.size(),
            buffer_data.data(), GL_DYNAMIC_DRAW);
}
