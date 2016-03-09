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

        void    select(void);
        void    unselect(void);

    public:
        ///
        /// \brief Initialise the vertex, (set the boundary and regular
        ///     attribute).
        ///
        void    initialise(void);

        ///
        /// \brief Return the valence of the vertex.
        ///
        unsigned int    valence(void) const;

    public:
        ///
        /// \brief Return the id of the vertex.
        ///
        unsigned int    id(void) const;

        ///
        /// \brief Return the position of the vertex.
        ///
        const glm::vec3     &position(void) const;

        ///
        /// \brief Return the face of the vertex.
        ///
        SDFace  *face(void) const;

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
        /// \brief Change the id of the vertex by the one in parameter.
        ///
        void    id(unsigned int id);

        ///
        /// \brief Change the vertex position to a new position.
        ///
        void    position(const glm::vec3 &position);

        ///
        /// \brief Change the value of the m_face field by the one in parameter.
        ///
        void    face(SDFace *face);

        ///
        /// \brief Change the value of the m_regular field by the one in param.
        ///
        void    regular(bool regular);

        ///
        /// \brief Change the value of the m_boundary field by the one in param.
        ///
        void    boundary(bool boundary);

    private:
        ///
        /// \brief specialised valence computation for non boundary vertex.
        ///
        unsigned int    non_boundary_valence(void) const;

        ///
        /// \brief Specialised valence computation for boundary vertex.
        ///
        unsigned int    boundary_valence(void) const;

    private:
        ///
        /// \brief The id of the vertex.
        ///
        unsigned int    m_id;

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
