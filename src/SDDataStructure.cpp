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
#include    "SDEdge.hpp"
#include    "SDFace.hpp"
#include    "SDVertex.hpp"

SDDataStructure::SDDataStructure(
        const std::vector<unsigned int> &indices,
        const std::vector<glm::vec3> &vertex_positions) :
    m_faces(),
    m_vertices(),
    m_edges()
{
    if (indices.size() % 3 != 0)
    {
        throw std::runtime_error("Number of indices doesn't match a"
                " triangulated mesh.");
    }
    this->build_connectivity(vertex_positions, indices);
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
    for (SDEdge *edge : this->m_edges)
    {
        delete edge;
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
        vertex->translate(vertex_positions[vertex_index]);
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
    this->build_edges_connectivity();
}

void
SDDataStructure::build_edges_connectivity(void)
{
    std::map<std::pair<unsigned int, unsigned int>, SDEdge *> existing_edges;

    for (SDFace *face : this->m_faces)
    {
        auto face_vertices = face->vertices();
        for (unsigned int index = 0 ; index < 3 ; ++index)
        {
            SDVertex *origin = face_vertices[index];
            SDVertex *target = face_vertices[(index + 1) % 3];
            SDEdge *edge = nullptr;
            bool left_face = true;
            if (origin->id() > target->id())
            {
                std::swap(origin, target);
                left_face = false;
            }
            auto key = std::make_pair(origin->id(), target->id());
            // check if the edge has been already created.
            auto it = existing_edges.find(key);
            if (it == existing_edges.end())
            {
                // we need to create a new edge between the origin and the
                // target.
                edge = this->build_edge(origin, target);
                // save the edge for the second face using the edge (if any).
                existing_edges.insert(std::make_pair(key, edge));
            }
            else
            {
                // the edge is equal to the previous edge created.
                edge = (*it).second;
                // because we don't support non manifold edge, we can delete it.
                existing_edges.erase(it);
            }
            // set the face of the edge to the actual face.
            if (left_face)
                edge->left_face(face);
            else
                edge->right_face(face);
        }
    }
}

SDEdge *
SDDataStructure::build_edge(SDVertex *origin, SDVertex *target)
{
    SDEdge  *edge = new SDEdge();

    edge->origin(origin);
    edge->target(target);
    return edge;
}
