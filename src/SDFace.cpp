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

#include    "SDFace.hpp"

SDFace::SDFace(void) :
    m_vertices(3, nullptr),
    m_adjacent_faces(3, nullptr),
    m_childrens_faces(4, nullptr)
{
    // nothing to do.
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

void
SDFace::vertex(unsigned int index, SDVertex *vertex)
{
    this->m_vertices[index] = vertex;
}
