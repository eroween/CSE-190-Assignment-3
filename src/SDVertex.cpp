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

#include    <algorithm>
#include    <iostream>

#include    "SDVertex.hpp"
#include    "SDFace.hpp"

SDVertex::SDVertex(void) :
    m_position(0.0f),
    m_face(nullptr),
    m_child_vertex(nullptr),
    m_regular(false),
    m_boundary(false)
{

}

SDVertex::~SDVertex(void)
{

}


void
SDVertex::select(void)
{
    SDFace  *face = this->m_face;

    std::cout << "valence value : " << this->valence() << std::endl;

    do
    {
        if (this->boundary())
            face->select(false, glm::vec3(0.0f, 0.0f, 1.0f));
        else
            face->select(false);
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->face());
    face = this->m_face;
    do
    {
        if (this->boundary())
            face->select(false, glm::vec3(0.0f, 0.0f, 1.0f));
        else
            face->select(false);
        face = face->right_adjacent_face(this);
    } while (face != nullptr && face != this->face());
}

void
SDVertex::unselect(void)
{
    SDFace  *face = this->m_face;

    do
    {
        face->unselect(false);
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->face());
    face = this->m_face;
    do
    {
        face->unselect(false);
        face = face->right_adjacent_face(this);
    } while (face != nullptr && face != this->face());
}


void
SDVertex::initialise(void)
{
    SDFace  *face = this->m_face;

    if (face == nullptr) return;
    do
    {
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->face());
    this->m_boundary = (face == nullptr);

    if ((this->boundary() && this->valence() == 6) ||
            (!this->boundary() && this->valence() == 4))
    {
        this->m_regular = true;
    }
}

void
SDVertex::generate_child_vertex(void)
{
    if (this->m_child_vertex == nullptr)
    {
        SDVertex *child = new SDVertex();
        child->m_position = this->m_position;
        child->m_boundary = this->m_boundary;
        child->m_regular = this->m_regular;
        this->m_child_vertex = child;
    }
}

unsigned int
SDVertex::valence(void) const
{
    if (this->boundary())
        return this->boundary_valence();
    return this->non_boundary_valence();
}

unsigned int
SDVertex::non_boundary_valence(void) const
{
    SDFace *face = this->m_face;
    int valence = 0;

    do
    {
        valence += 1;
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->m_face);
    return valence;
}

unsigned int
SDVertex::boundary_valence(void) const
{
    SDFace *face = this->m_face;
    int valence = 0;

    do
    {
        valence += 1;
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->m_face);
    face = this->face();
    do
    {
        valence += 1;
        face = face->right_adjacent_face(this);
    } while (face != nullptr && face != this->m_face);
    return valence;
}

std::vector<SDVertex *>
SDVertex::adjacent_vertices(void) const
{
    std::vector<SDVertex *>     result;
    auto faces = this->adjacent_faces();

    for (SDFace *face : faces)
    {
        auto face_vertices = face->vertices();
        for (SDVertex *vertex : face_vertices)
        {
            if (vertex != this && std::find(result.begin(), result.end(), vertex) == result.end())
            {
                result.push_back(vertex);
            }
        }
    }
    return result;
}

std::vector<SDFace *>
SDVertex::adjacent_faces(void) const
{
    if (this->boundary())
        return this->boundary_adjacent_faces();
    return this->non_boundary_adjacent_faces();
}

std::vector<SDFace *>
SDVertex::boundary_adjacent_faces(void) const
{
    std::vector<SDFace *>   result;
    SDFace *face = this->m_face;

    do
    {
        result.push_back(face);
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->m_face);
    face = this->face();
    face = face->right_adjacent_face(this);
    while (face != nullptr && face != this->m_face)
    {
        result.push_back(face);
        face = face->right_adjacent_face(this);
    }
    return result;
}

std::vector<SDFace *>
SDVertex::non_boundary_adjacent_faces(void) const
{
    std::vector<SDFace *>   result;
    SDFace *face = this->m_face;

    do
    {
        result.push_back(face);
        face = face->left_adjacent_face(this);
    } while (face != nullptr && face != this->m_face);
    return result;
}

const glm::vec3 &
SDVertex::position(void) const
{
    return this->m_position;
}

SDFace *
SDVertex::face(void) const
{
    return this->m_face;
}

SDVertex *
SDVertex::child(void) const
{
    return this->m_child_vertex;
}

bool
SDVertex::regular(void) const
{
    return this->m_regular;
}

bool
SDVertex::boundary(void) const
{
    return this->m_boundary;
}



void
SDVertex::face(SDFace *face)
{
    this->m_face = face;
}

void
SDVertex::regular(bool regular)
{
    this->m_regular = regular;
}

void
SDVertex::boundary(bool boundary)
{
    this->m_boundary = boundary;
}

void
SDVertex::position(const glm::vec3 &position)
{
    this->m_position = position;
}
