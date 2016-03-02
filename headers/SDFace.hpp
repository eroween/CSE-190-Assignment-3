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
        ///
        /// \brief Return a vector containing all vertices used by the face.
        ///
        std::vector<SDVertex *>     vertices(void) const;

        ///
        /// \brief Return a vector containing all adjacent faces.
        ///
        std::vector<SDFace *>       adjacent_faces(void) const;

        ///
        /// \brief Return a vector containing all childrens faces.
        ///
        std::vector<SDFace *>       childrens_faces(void) const;

    private:
        SDVertex    *m_vertices[3];
        SDFace      *m_adjacent_faces[3];
        SDFace      *m_childrens[4];

};
