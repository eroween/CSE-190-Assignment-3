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

#pragma once

#include    <glm/glm.hpp>

class   SDFace;

class   SDVertex
{
    public:
        ///
        /// \brief Default constructor.
        ///
        SDVertex(void);

        ///
        /// \brief Destructor
        ///
        ~SDVertex(void);

    public:

        ///
        /// \brief Return the position of the vertex.
        ///
        const glm::vec3     &position(void) const;

        ///
        /// \brief Return true if the vertex is a regular vertex, false
        /// otherwise.
        ///
        bool    regular(void) const;

        ///
        /// \brief Return true if the vertex is a boundary vertex, false
        /// otherwise.
        ///
        bool    boundary(void) const;

    public:

        ///
        /// \brief The position value of the vertex.
        ///
        glm::vec3   m_position;

        ///
        /// \brief The child vertex, the child vertex is the right child vertex.
        ///
        SDVertex    *m_child_vertex;

        ///
        /// \brief A pointer to one face using the vertex.
        ///
        SDFace  *m_face;

        ///
        /// \brief Contains the state of the vertex for the regular or not
        /// regular state. A regular vertex is a vertex with 6 outgoing edge
        /// or 3 outgoing edge if the vertex is a boundary one.
        ///
        bool    m_regular;

        ///
        /// \brief Contains the state of the vertex, if the vertex is a boundary
        /// one, the m_boundary must be set to true, if not, it should be set to
        /// false.
        ///
        bool    m_boundary;
};
