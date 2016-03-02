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

#include    "SDEdge.hpp"

SDEdge::SDEdge(void) :
    m_id(-1),
    m_origin(nullptr),
    m_target(nullptr),
    m_left_face(nullptr),
    m_right_face(nullptr)
{

}

SDEdge::~SDEdge(void)
{

}



unsigned int
SDEdge::id(void) const
{
    return this->m_id;
}

SDVertex *
SDEdge::origin(void) const
{
    return this->m_origin;
}

SDVertex *
SDEdge::target(void) const
{
    return this->m_target;
}

SDFace *
SDEdge::left_face(void) const
{
    return this->m_left_face;
}

SDFace *
SDEdge::right_face(void) const
{
    return this->m_right_face;
}
