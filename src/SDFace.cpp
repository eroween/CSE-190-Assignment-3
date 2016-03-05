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
    m_normal(0.0f),
    m_vertices(3, nullptr),
    m_adjacent_faces(3, nullptr),
    m_childrens_faces(4, nullptr)
{
    // nothing to do.
}

SDFace::SDFace(SDVertex *v1, SDVertex *v2, SDVertex *v3) :
    m_color(glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f))),
    m_normal(0.0f),
    m_vertices(3, nullptr),
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
        SDVertex *v1 = this->m_vertices[0]->child_or_create();
        SDVertex *v2 = this->m_vertices[1]->child_or_create();
        SDVertex *v3 = this->m_vertices[2]->child_or_create();

        SDFace *f1 = new SDFace(this->m_vertices[0], v1, v3);
        SDFace *f2 = new SDFace(v1, this->m_vertices[1], v2);
        SDFace *f3 = new SDFace(v2, this->m_vertices[2], v3);
        SDFace *f4 = new SDFace(v1, v2, v3);

        v1->position(this->m_vertices[0]->position());
        v2->position(this->m_vertices[1]->position());
        v3->position(this->m_vertices[2]->position());

/*        v1->position((this->m_vertices[0]->position() + this->m_vertices[1]->position()) / 2.0f);*/
        //v2->position((this->m_vertices[1]->position() + this->m_vertices[2]->position()) / 2.0f);
        //v3->position((this->m_vertices[2]->position() + this->m_vertices[0]->position()) / 2.0f);

        this->m_childrens_faces[0] = f1;
        this->m_childrens_faces[1] = f2;
        this->m_childrens_faces[2] = f3;
        this->m_childrens_faces[3] = f4;
    }
}
