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
class   SDEdge;

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
        /// \brief Return a vector of indices that can be used to represent the
        ///     mesh with a graphic API.
        ///
        /// WARNING : complexity O(N)
        ///
        std::vector<unsigned int>   indices(void) const;

        ///
        /// \brief Return a vecotr of vertices that can be used to represent the
        ///     mesh with a graphic API.
        ///
        /// WARNING : complexity O(N)
        ///
        std::vector<glm::vec3>      vertices(void) const;

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
        /// \brief Construct the edges from the list of faces and the list of
        ///     vertices.
        ///
        void    build_edges_connectivity(void);

        ///
        /// \brief Create an edge with an origin and a target vertex.
        /// \return The new allocated edge.
        ///
        SDEdge  *build_edge(SDVertex *origin, SDVertex *target);

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
        /// \brief The list of edges compositing the mesh.
        ///
        std::list<SDEdge *>     m_edges;
};