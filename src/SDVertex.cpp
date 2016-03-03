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

#include    "SDVertex.hpp"
#include    "SDFace.hpp"

SDVertex::SDVertex(void) :
    m_position(0.0f),
    m_child_vertex(nullptr),
    m_face(nullptr),
    m_regular(false),
    m_boundary(false)
{

}

SDVertex::~SDVertex(void)
{

}


void
SDVertex::initialise(void)
{
    SDFace  *face = this->m_face;

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



unsigned int
SDVertex::id(void) const
{
    return this->m_id;
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
SDVertex::id(unsigned int id)
{
    this->m_id = id;
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
