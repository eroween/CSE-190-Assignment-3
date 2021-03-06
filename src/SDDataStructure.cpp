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

#include    <map>
#include    <iostream>

#include    "SDDataStructure.hpp"
#include    "SDFace.hpp"
#include    "SDVertex.hpp"

using SDEdge = std::pair<SDVertex *, SDVertex *>;

SDDataStructure::SDDataStructure(
        const std::vector<unsigned int> &indices,
        const std::vector<glm::vec3> &vertex_positions) :
    m_faces(),
    m_vertices(),
    m_subdivision_level(0)
{
    if (indices.size() % 3 != 0)
    {
        throw std::runtime_error("Number of indices doesn't match a"
                " triangulated mesh.");
    }

    std::cout << "number of indices : " << indices.size() << std::endl;
    std::cout << "number of vertices : " << vertex_positions.size() << std::endl;

    this->build_connectivity(vertex_positions, indices);
    this->initialise_faces();
    this->initialise_vertices();
}

SDDataStructure::~SDDataStructure(void)
{
    for (SDVertex *vertex : this->m_vertices)
    {
        delete vertex;
    }
    for (SDFace *face : this->m_faces)
    {
        delete face;
    }
}


void
SDDataStructure::debug(int val)
{
    if (val == 0 || val == 1)
    {
        static int  face_num = 0;

        auto it = this->m_faces.begin();
        std::advance(it, face_num);

        (*it)->unselect(true);

        if (val == 0)
        {
            face_num = face_num + 1;
            face_num = face_num > (int)this->m_faces.size() - 1 ? 0 : face_num;

            auto nit = this->m_faces.begin();

            std::advance(nit, face_num);
            (*nit)->select(true);
        }
    }
    else if (val == 2 || val == 3)
    {
        static int  vertice_num = 0;

        auto it = this->m_vertices.begin();
        std::advance(it, vertice_num);

        (*it)->unselect();

        vertice_num = val == 1 ? vertice_num - 1 : vertice_num + 1;
        vertice_num = vertice_num < 0 ? this->m_vertices.size() - 1 :
            vertice_num > (int)this->m_vertices.size() - 1 ? 0 : vertice_num;

        auto nit = this->m_vertices.begin();

        std::advance(nit, vertice_num);
        (*nit)->select();

    }
}


std::vector<float>
SDDataStructure::data(void) const
{
    std::vector<float>      data_vector;

    for (SDFace *face : this->m_faces)
    {
        const auto &face_data = face->data();
        data_vector.insert(data_vector.end(), face_data.begin(), face_data.end());
    }
    return data_vector;
}

unsigned int
SDDataStructure::data_size(void) const
{
    if (this->m_subdivision_level > 0)
        return this->m_faces.size() * std::pow(4, this->m_subdivision_level) * 3;
    return this->m_faces.size() * 3;
}



void
SDDataStructure::subdivide(void)
{
    ++this->m_subdivision_level;
    for (SDFace *face : this->m_faces)
    {
        face->subdivide();
    }
    this->initialise_faces();
}



void
SDDataStructure::build_connectivity(
        const std::vector<glm::vec3> &vertex_positions,
        const std::vector<unsigned int> &indices)
{
    std::vector<SDVertex *> allocated_vertices;

    allocated_vertices.reserve(vertex_positions.size());
    for (unsigned int vertex_index = 0 ;
            vertex_index < vertex_positions.size() ; ++vertex_index)
    {
        // get the preallocated vertex in order to initialize it.
        SDVertex    *vertex = new SDVertex();
        // translate the allocated vertex to its position.
        vertex->position(vertex_positions[vertex_index]);
        // add the vertex in the list of vertex known by the datastructure.
        this->m_vertices.push_back(vertex);
        allocated_vertices.push_back(vertex);
    }
    for (unsigned int face_index = 0 ;
            face_index < indices.size() / 3 ; ++face_index)
    {
        // Get the preallocated face in order to initialize it.
        SDFace  *face = new SDFace();

        for (unsigned int vertex_index = 0 ; vertex_index < 3 ; ++vertex_index)
        {
            unsigned int    vertex_id = indices[face_index * 3 + vertex_index];
            // get the preallocated vertex.
            SDVertex   *vertex = allocated_vertices[vertex_id];
            // set the face of the vertex to the actual face.
            vertex->face(face);
            // set the vertex_index of the face to the vertex.
            face->vertex(vertex_index, vertex);
        }
        this->m_faces.push_back(face);
    }
    for (auto it = this->m_vertices.begin() ; it != this->m_vertices.end() ; )
    {
        if ((*it)->face() == nullptr)
        {
            it = this->m_vertices.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void
SDDataStructure::initialise_faces(void)
{
    std::map<SDEdge, std::pair<SDFace *, unsigned int>>   edges;

    for (SDFace *face : this->m_faces)
    {
        face->initialise(edges);
    }
}

void
SDDataStructure::initialise_vertices(void)
{
    for (SDVertex *vertex : this->m_vertices)
    {
        vertex->initialise();
    }
}

