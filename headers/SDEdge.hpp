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

class   SDEdge
{
    public:
        ///
        /// \brief Default constructor.
        ///
        SDEdge(void);

        ///
        /// \brief Destructor.
        ///
        ~SDEdge(void);

    public:
        bool    operator<(const SDEdge &other);

    public:

        unsigned int    id(void);
        SDVertex    *origin(void);
        SDVertex    *target(void);
        SDFace      *left_face(void);
        SDFace      *right_face(void);

    private:
        ///
        /// \brief the id of the edge.
        ///
        unsigned int    m_id;

        ///
        /// \brief The origin vertex of the Edge.
        ///
        SDVertex    *m_origin;

        ///
        /// \brief The target vertex of the edge.
        ///
        SDVertex    *m_target;

        ///
        /// \brief The left face of the edge, the face can be null if the edge
        /// is a boundary one.
        ///
        /// Both left_face and right_face should not be null.
        ///
        SDFace      *m_left_face;

        ///
        /// \brief The right face of the edge, the face can be null if the edge
        /// is a boundary one.
        ///
        /// Both left_face and right_face should not be null.
        ///
        SDFace      *m_right_face;

};
