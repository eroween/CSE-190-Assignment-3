#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Mesh.hpp"
#include "HalfEdge.hpp"
#include "Vertex.hpp"

Mesh *mesh;

int main(int argc, char** argv)
{
    mesh = new Mesh("/Users/camel/Dropbox/CSE190/Assigment_3/Mesh_Editor/models/testpatch.off");//testpatch.
    //return 0;
}
