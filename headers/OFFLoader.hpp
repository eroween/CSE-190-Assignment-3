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

#pragma     once

#include    <string>
#include    <vector>

class   Mesh;

class   OFFLoader
{
    public:
        ///
        /// \brief Load a mesh from a path.
        ///
        static Mesh *   load(const std::string &path);

    private:
        ///
        /// \brief Split a string by a delim value.
        ///
        /// https://stackoverflow.com/questions/236129/split-a-string-in-c
        ///
        static std::vector<std::string> & split(const std::string &str,
                char delim, std::vector<std::string> &elems);
};
