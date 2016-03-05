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
#include    <list>
#include    <glm/glm.hpp>

class   SDVertex;
class   SDFace;

class   SDDataStructure
{
    public:
        ///
        /// \brief Default constructor.
        /// \param vertices A vector of vertex.
        /// \param indices A vector of indices to vertex. Each 3 indices must
        ///     be a face.
        ///
        SDDataStructure(const std::vector<unsigned int> &indices,
                const std::vector<glm::vec3> &vertex_positions);

        ///
        /// \brief Destructor.
        ///
        ~SDDataStructure(void);

    public:
        ///
        /// \brief Computed vertices data with indices (drawArray).
        ///
        std::vector<float>          data(void) const;

        ///
        /// \brief Return the number of vertices in the mesh datastructure.
        ///
        unsigned int    data_size(void) const;

    public:
        ///
        /// \brief Subdivide the mesh datastructure by one level.
        ///
        void    subdivide(void);

    private:
        ///
        /// \brief This method is used to build the connectivity of the mesh.
        /// \param vertices A vector of vertex.
        /// \param indices A vector of indices to vertex. Each 3 indices must
        ///     be a face.
        ///
        void    build_connectivity(const std::vector<glm::vec3> &vertices,
                const std::vector<unsigned int> &indices);

        ///
        /// \brief Initialise the faces compositing the mesh.
        ///
        void    initialise_faces(void);

        ///
        /// \brief Initialise all vertices compositing the mesh.
        ///
        void    initialise_vertices(void);

    private:
        ///
        /// \brief The list of face compositing the mesh.
        ///
        std::list<SDFace *>     m_faces;

        ///
        /// \brief The list of vertices compositing the mesh.
        ///
        std::list<SDVertex *>   m_vertices;

        ///
        /// \brief Store the actual subdivision level.
        ///
        unsigned int            m_subdivision_level;
};
