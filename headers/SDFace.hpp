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

#include    <vector>

class   SDVertex;

class   SDFace
{
    public:
        ///
        /// \brief Default constructor.
        ///
        SDFace(void);

        ///
        /// \brief Destructor.
        ///
        ~SDFace(void);

    public:

        SDFace  *left_adjacent_face(const SDVertex *vertex) const;
        SDFace  *right_adjacent_face(const SDVertex *vertex) const;

    public:
        ///
        /// \brief Return a vector containing all vertices used by the face.
        ///
        const std::vector<SDVertex *>   &vertices(void) const;

        ///
        /// \brief Return a vector containing all adjacent faces.
        ///
        const std::vector<SDFace *>     &adjacent_faces(void) const;

        ///
        /// \brief Return a vector containing all childrens faces.
        ///
        const std::vector<SDFace *>     &childrens_faces(void) const;

    public:
        ///
        /// \brief Change the value of the vertex at the index "index" by the
        ///     "vertex" value.
        ///
        void    vertex(unsigned int index, SDVertex *vertex);

        ///
        /// \brief
        ///
        void    adjacent_face(unsigned int index, SDFace *face);

    private:
        ///
        /// \brief The vector of vertices
        ///
        /// The size of the vector is always 3, because we only support
        /// triangle face.
        ///
        std::vector<SDVertex *>     m_vertices;

        ///
        /// \brief The vector of adjacent faces.
        ///
        /// The size of the vector is always 3, but some face can be null.
        ///
        std::vector<SDFace *>   m_adjacent_faces;

        ///
        /// \brief The vector of childrens faces.
        ///
        /// The size of the vector is always 4, but all face can be null.
        ///
        std::vector<SDFace *>   m_childrens_faces;
};
