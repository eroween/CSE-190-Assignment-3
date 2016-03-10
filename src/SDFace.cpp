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

#include    <iostream>
#include    <glm/gtc/random.hpp>

#include    "SDFace.hpp"
#include    "SDVertex.hpp"

SDFace::SDFace(void) :
    m_color(glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f))),
    m_color_tmp(m_color),
    m_normal(0.0f),
    m_vertices(3, nullptr),
    m_vertices_child(3, nullptr),
    m_adjacent_faces(3, nullptr),
    m_childrens_faces(4, nullptr)
{
    // nothing to do.
}

SDFace::SDFace(SDVertex *v1, SDVertex *v2, SDVertex *v3) :
    m_color(glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f))),
    m_color_tmp(m_color),
    m_normal(0.0f),
    m_vertices(3, nullptr),
    m_vertices_child(3, nullptr),
    m_adjacent_faces(3, nullptr),
    m_childrens_faces(4, nullptr)
{
    this->m_vertices[0] = v1;
    this->m_vertices[1] = v2;
    this->m_vertices[2] = v3;
}

SDFace::~SDFace(void)
{
    // nothing to do, only pointer that should not be freed.
}


void
SDFace::initialise(std::map<SDEdge, std::pair<SDFace *, unsigned int>> &edges)
{
    if (this->m_childrens_faces[0] != nullptr)
    {
        for (SDFace *child : this->m_childrens_faces)
        {
             child->initialise(edges);
        }
    }
    else
    {
        std::map<SDEdge, std::pair<SDFace *, unsigned int>>::iterator it;

        auto face_vertices = this->vertices();
        for (unsigned int index = 0 ; index < 3 ; ++index)
        {
            auto edge = std::make_pair(face_vertices[index],
                    face_vertices[(index + 1) % 3]);
            if (edge.first > edge.second)
                std::swap(edge.first, edge.second);
            if ((it = edges.find(edge)) != edges.end())
            {
                (*it).second.first->adjacent_face((*it).second.second, this);
                this->adjacent_face(index, (*it).second.first);
                edges.erase(it);
            }
            else
            {
                auto value = std::make_pair(this, index);
                edges.insert(std::make_pair(edge, value));
            }
        }
    }

}

void
SDFace::select(bool with_children, const glm::vec3 &color)
{
    if (this->m_childrens_faces[0] != nullptr)
    {
        this->m_childrens_faces[0]->select(true);
        this->m_childrens_faces[1]->select(true);
        this->m_childrens_faces[2]->select(true);
        this->m_childrens_faces[3]->select(true);

        this->m_childrens_faces[0]->select(false);
        this->m_childrens_faces[1]->select(false);
        this->m_childrens_faces[2]->select(false);
        this->m_childrens_faces[3]->select(false);
    }
    else
    {
        this->m_color = color;

        if (with_children)
        {
            auto f1 = this->m_adjacent_faces[0];
            auto f2 = this->m_adjacent_faces[1];
            auto f3 = this->m_adjacent_faces[2];

            if (f1 != nullptr)
                f1->m_color = glm::vec3(1.0f, 0.5f, 0.5f);
            if (f2 != nullptr)
                f2->m_color = glm::vec3(1.0f, 0.5f, 0.5f);
            if (f3 != nullptr)
                f3->m_color = glm::vec3(1.0f, 0.5f, 0.5f);
        }
    }
}

void
SDFace::unselect(bool with_children)
{
    if (this->m_childrens_faces[0] != nullptr)
    {
        this->m_childrens_faces[0]->unselect(true);
        this->m_childrens_faces[1]->unselect(true);
        this->m_childrens_faces[2]->unselect(true);
        this->m_childrens_faces[3]->unselect(true);

        this->m_childrens_faces[0]->unselect(false);
        this->m_childrens_faces[1]->unselect(false);
        this->m_childrens_faces[2]->unselect(false);
        this->m_childrens_faces[3]->unselect(false);
    }
    else
    {
        this->m_color = this->m_color_tmp;

        if (with_children)
        {
            auto f1 = this->m_adjacent_faces[0];
            auto f2 = this->m_adjacent_faces[1];
            auto f3 = this->m_adjacent_faces[2];

            if (f1 != nullptr)
                f1->m_color = f1->m_color_tmp;
            if (f2 != nullptr)
                f2->m_color = f2->m_color_tmp;
            if (f3 != nullptr)
                f3->m_color = f3->m_color_tmp;
        }
    }
}

const std::vector<SDVertex *> &
SDFace::vertices(void) const
{
     return this->m_vertices;
}

const std::vector<SDFace *> &
SDFace::adjacent_faces(void) const
{
    return this->m_adjacent_faces;
}

const std::vector<SDFace *> &
SDFace::childrens_faces(void) const
{
    return this->m_childrens_faces;
}

const glm::vec3 &
SDFace::color(void) const
{
    return this->m_color;
}

const glm::vec3 &
SDFace::normal(void) const
{
    return this->m_normal;
}

std::vector<float>
SDFace::data(void) const
{
    std::vector<float> data_vector;
    if (this->m_childrens_faces[0] != nullptr)
    {
        for (unsigned int i = 0 ; i < this->m_childrens_faces.size() ; ++i)
        {
            auto child_data = this->m_childrens_faces[i]->data();
            data_vector.insert(data_vector.end(), child_data.begin(), child_data.end());
        }
    }
    else
    {
        for (SDVertex *vertex : this->m_vertices)
        {
            data_vector.push_back(vertex->position().x);
            data_vector.push_back(vertex->position().y);
            data_vector.push_back(vertex->position().z);

            data_vector.push_back(this->color().x);
            data_vector.push_back(this->color().y);
            data_vector.push_back(this->color().z);

            // face normal for flat shadding.
            data_vector.push_back(this->normal().x);
            data_vector.push_back(this->normal().y);
            data_vector.push_back(this->normal().z);

        }
    }
    return data_vector;
}



void
SDFace::vertex(unsigned int index, SDVertex *vertex)
{
    this->m_vertices[index] = vertex;
}

void
SDFace::adjacent_face(unsigned int index, SDFace *face)
{
    this->m_adjacent_faces[index] = face;
}



SDFace *
SDFace::left_adjacent_face(const SDVertex *vertex) const
{
    if (this->m_vertices[0] == vertex)
        return this->m_adjacent_faces[2];
    else if (this->m_vertices[1] == vertex)
        return this->m_adjacent_faces[0];
    return this->m_adjacent_faces[1];
}

SDFace *
SDFace::right_adjacent_face(const SDVertex *vertex) const
{
    if (this->m_vertices[0] == vertex)
        return this->m_adjacent_faces[0];
    else if (this->m_vertices[1] == vertex)
        return this->m_adjacent_faces[1];
    return this->m_adjacent_faces[2];
}

void
SDFace::subdivide(void)
{
    if (this->m_childrens_faces[0] != nullptr)
    {
        for (auto child_face : this->m_childrens_faces)
        {
            child_face->subdivide();
        }
    }
    else
    {
        this->generate_child_vertices();
        this->generate_child_faces();
    }
}

void
SDFace::generate_child_vertices(void)
{
    // The v0 && v1 are only used to set the position in the middle of the two
    // vertex. I think that should be removed with a proper implementation of the
    // new position.
    auto generate_child_vertex = [this](unsigned int index,
            SDVertex *v0, SDVertex *v1){
        if (this->m_vertices_child[index] == nullptr)
        {
            SDVertex *vertex = new SDVertex();
            vertex->regular(true);
            vertex->boundary(this->m_adjacent_faces[index] == nullptr);

            vertex->position(v0->position() + 0.5f * (v1->position() - v0->position()));

            this->m_vertices_child[index] = vertex;
            if (this->m_adjacent_faces[index] != nullptr)
            {
                this->m_adjacent_faces[index]->update_child_vertex(this, vertex);
            }
        }
    };
    generate_child_vertex(0, this->m_vertices[0], this->m_vertices[1]);
    generate_child_vertex(1, this->m_vertices[1], this->m_vertices[2]);
    generate_child_vertex(2, this->m_vertices[2], this->m_vertices[0]);
    this->m_vertices[0]->generate_child_vertex();
    this->m_vertices[1]->generate_child_vertex();
    this->m_vertices[2]->generate_child_vertex();
}

void
SDFace::generate_child_faces(void)
{
    auto generate_child_face = [this](unsigned int index, SDVertex *v1,
            SDVertex *v2, SDVertex *v3){
        SDFace *face = new SDFace(v1, v2, v3);
        v1->face(face);
        v2->face(face);
        v3->face(face);
        this->m_childrens_faces[index] = face;
    };
    generate_child_face(0, this->m_vertices[0]->child(), this->m_vertices_child[0], this->m_vertices_child[2]);
    generate_child_face(1, this->m_vertices_child[0], this->m_vertices[1]->child(), this->m_vertices_child[1]);
    generate_child_face(2, this->m_vertices_child[1], this->m_vertices[2]->child(), this->m_vertices_child[2]);
    generate_child_face(3, this->m_vertices_child[0], this->m_vertices_child[1], this->m_vertices_child[2]);
}

void
SDFace::update_child_vertex(SDFace *face, SDVertex *vertex)
{
    unsigned int    position;

    for (position = 0 ; position < 3 && this->m_adjacent_faces[position] != face
            ; ++position);
    this->m_vertices_child[position] = vertex;
}
