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

#include    <fstream>
#include    <sstream>

#include    "OFFLoader.hpp"
#include    "Mesh.hpp"

Mesh *
OFFLoader::load(const std::string &path)
{
    std::vector<std::string> tokens;
    std::ifstream   file(path);
    std::string line = "";

    std::vector<unsigned int> indices;
    std::vector<glm::vec3>  vertex_positions;

    unsigned int face_numbers = 0;
    unsigned int vertex_numbers = 0;

    while (std::getline(file, line))
    {
        tokens.clear();
        tokens = OFFLoader::split(line, ' ', tokens);

        if (tokens.at(0).compare("OFF") == 0)
        {
            continue;
        }

        if (face_numbers == 0)
        {
            face_numbers = std::stoi(tokens.at(0));
            vertex_numbers = std::stoi(tokens.at(1));

            vertex_positions.reserve(vertex_numbers);
            indices.reserve(face_numbers * 3);
        }


        if (tokens.size() == 3)
        {
            vertex_positions.emplace_back(std::stof(tokens.at(0)),
                    std::stof(tokens.at(1)), std::stof(tokens.at(2)));
        }
        if (tokens.size() == 4)
        {
            indices.push_back(std::stoi(tokens.at(1))+1);
            indices.push_back(std::stoi(tokens.at(2))+1);
            indices.push_back(std::stoi(tokens.at(3))+1);
        }
    }
    return new Mesh(indices, vertex_positions);
}

std::vector<std::string> &
OFFLoader::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

