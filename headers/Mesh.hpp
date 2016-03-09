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

#pragma once

#include    <vector>
#include    <glm/glm.hpp>

#include    "SDDataStructure.hpp"

class Mesh
{
public:

    ///
    /// \brief Default Constructor.
    ///
    Mesh(const std::vector<unsigned int> &indices,
            const std::vector<glm::vec3> &vertex_positions);

    ///
    /// \brief Destructor.
    ///
    ~Mesh(void);

public:

    void    debug(int);

public:
    ///
    /// \brief Move the mesh at a specific position.
    ///
    /// In this program, the mesh is considered as an instantiated object.
    ///
    void    translate(const glm::vec3 &position);

    ///
    /// \brief Clear the matrix stack
    ///
    void reset();

    ///
    /// \brief Rotate the mesh on The X axis
    ///
    void    rotate(float degree, const glm::vec3 &angles);

    ///
    /// \brief Scale the mesh.
    ///
    void    scale(const glm::vec3 &scale);

public:
    ///
    /// \brief Bind the mesh in the graphic pipeline.
    ///
    void    bind(unsigned int program_shader_id);

    ///
    /// \brief Subdivide the mesh by one level.
    ///
    void    subdivide(void);

public:
    ///
    /// \brief Return the model matrix.
    ///
    const glm::mat4 &model(void) const;

    ///
    /// \brief The data size of the mesh.
    ///
    unsigned int    data_size(void) const;

private:
    ///
    /// \brief Update the mesh in the graphic card.
    ///
    void    update(void);

private:
    ///
    /// \brief The mesh datastructure used by the mesh to contains its data.
    ///
    SDDataStructure     m_datastructure;

    ///
    /// \brief The model matrix of the object.
    ///
    glm::mat4           m_model;

    ///
    /// \brief OpenGL specific, the vertex buffer id of the mesh.
    ///
    unsigned int        m_vertex_buffer_id;

    ///
    /// \brief OpenGL specific, the element buffer id of the mesh.
    ///
    unsigned int        m_element_buffer_id;
};
