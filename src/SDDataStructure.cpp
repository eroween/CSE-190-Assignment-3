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
    m_vertices()
{
    if (indices.size() % 3 != 0)
    {
        throw std::runtime_error("Number of indices doesn't match a"
                " triangulated mesh.");
    }
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



std::vector<unsigned int>
SDDataStructure::indices(void) const
{
    std::vector<unsigned int>   indices;

    indices.reserve(this->m_faces.size() * 3);
    for (SDFace *face : this->m_faces)
    {
        auto vertices = face->vertices();
        for (SDVertex *vertex : vertices)
        {
            indices.push_back(vertex->id());
        }
    }
    return indices;
}

std::vector<glm::vec3>
SDDataStructure::vertices(void) const
{
    std::vector<glm::vec3>  vertices;

    vertices.reserve(this->m_vertices.size());
    for (SDVertex *vertex : this->m_vertices)
    {
        vertices.push_back(vertex->position());
    }
    return vertices;
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
        // set the id of the vertex.
        vertex->id(vertex_index);
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
}

void
SDDataStructure::initialise_faces(void)
{
    std::map<SDEdge, std::pair<SDFace *, unsigned int>>   edges;
    std::map<SDEdge, std::pair<SDFace *, unsigned int>>::iterator it;

    for (SDFace *face : this->m_faces)
    {
        auto face_vertices = face->vertices();
        for (unsigned int index = 0 ; index < 3 ; ++index)
        {
            auto edge = std::make_pair(face_vertices[index],
                    face_vertices[(index + 1) % 3]);
            if (edge.first->id() > edge.second->id())
                std::swap(edge.first, edge.second);
            if ((it = edges.find(edge)) != edges.end())
            {
                (*it).second.first->adjacent_face((*it).second.second, face);
                face->adjacent_face(index, (*it).second.first);
            }
            else
            {
                auto value = std::make_pair(face, index);
                edges.insert(std::make_pair(edge, value));
            }
        }
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

