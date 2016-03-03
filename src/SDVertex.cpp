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
SDVertex::translate(const glm::vec3 &position)
{
    this->m_position = position;
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
