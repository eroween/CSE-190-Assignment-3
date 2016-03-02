
#include "Mesh.hpp"
#include <fstream>
#include <sstream>
#include "Matrix4.hpp"

#include <string>


Mesh::Mesh(std::string filename)
{
    numOFinputFaces     = 0;
    numOfInputVertices  = 0;
    loadObject(filename);
    initMesh();
    //test();
}


Mesh::~Mesh()
{
	 DEBUG_PRINT("TODO\n");
}

double * Mesh::getVertexData()
{
    double *temp = (double*)(&outputData)[0];
    return temp;

}

int Mesh::getNunOfVertices()
{
    return numOfVertices;
}

std::vector<std::string>& Mesh::split(const std::string &s,
                                      char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<Face*> Mesh::findFacesAroundFace(Face *f)
{
    std::vector<Face *> faces;
    HalfEdge *e0 = f->getHalfEdge();
    HalfEdge *edge = e0;
    do
    {
        edge = edge->getNext();
        if(edge->getTwin() != NULL)
            faces.push_back(edge->getTwin()->getFace());
    }while(edge != e0);
    return faces;
}

std::vector<Face*> Mesh::findFacesAroundVertex(Vertex *v)
{
    std::vector<HalfEdge*> edges;
    std::vector<Face*> faces;
    edges = findEdgesEnteringVertex(v);
    for(std::vector<HalfEdge*>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        Face *f = (*it)->getFace();
        if(f != NULL)
            faces.push_back(f);
    }

    return faces;
}

std::vector<HalfEdge*> Mesh::findEdgesEnteringVertex(Vertex *v)
{
    std::vector<HalfEdge*> edges;
    HalfEdge *e0    = v->getHalfEdge();
    HalfEdge *edge  = e0;
    int i = 0;
    do
    {
        if(edge->getTwin() != NULL)
        {
            if(edge->getTwin()->getPrev() != NULL)
            {
                edge = edge->getTwin()->getPrev();
                edges.push_back(edge);
            }
        }
    }while(edge != e0);
    return edges;
}

std::vector<HalfEdge*> Mesh::findEdgesLeavingVertex(Vertex *v)
{
    std::vector<HalfEdge*> edges;
    HalfEdge *e0    = v->getHalfEdge();
    HalfEdge *edge  = e0;
    do
    {
        if(edge->getNext() != NULL)
        {
            edge = edge->getNext();
            edges.push_back(edge);
        }
        if(edge->getTwin() != NULL)
        edge = edge->getTwin();
    }while(edge != e0);

    return edges;
}

void Mesh::loadObject(const std::string filename)
{

    FILE * file;
    int faceCounter = 0;
    int vertCounter = 0;
    std::string line;
    Vector4D color;

    std::ifstream infile(filename);

    std::vector<std::string> tokens;
    std::string token;
    std::vector<std::string> tok;

    const char * c = filename.c_str();

    file = fopen(c,"rb");

    std::cout << "Starting parse..." << std::endl;

    while (std::getline(infile, line))
    {
        //Split a line into tokens by delimiting it on spaces
        tokens.clear();
        tokens = split(line, ' ', tokens);

        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("OFF") == 0)
        {
            std::cout<<"OFF"<< std::endl;
            continue;
        }
        if(numOFinputFaces == 0)
        {
            numOfInputVertices = std::stof(tokens.at(0));
            numOFinputFaces = std::stof(tokens.at(1));
        }
        if(tokens.size() == 3)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(0));
            float y = std::stof(tokens.at(1));
            float z = std::stof(tokens.at(2));

            Vector3D position = Vector3D(x,y,z);
            Vertex *ver = new Vertex(position);

            ver->setHalfEdge(NULL);
            ver->id = vertCounter;

            inputVertex.push_back(ver);
            vertCounter++;

        }
        if(tokens.size() == 4)
        {
            //generate a random color for each face.
            color[0] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[1] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[2] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[3] = 1;

            int x = std::stof(tokens.at(1)) ;//+ 1;
            int y = std::stof(tokens.at(2)) ;//+ 1;
            int z = std::stof(tokens.at(3)) ;//+ 1;

            int fv[] = {x,y,z};

            Face *f = new Face(fv, color);
            f->id = faceCounter;

            inputFaces.push_back(f);
            faceCounter++;
        }
    }
    std::cout << "Done parsing." << std::endl;
}

void Mesh::buildHalfEdgeConnections(HalfEdge *e0, HalfEdge *e1, HalfEdge *e2)
{
    e0->setPrev(e2);
    e0->setNext(e1);

    e1->setPrev(e0);
    e1->setNext(e2);

    e2->setPrev(e1);
    e2->setNext(e0);

}

void Mesh::createData(int i, Face *f)
{
    //generate a random color for each face.
    Vertex *v0;
    Vertex *v1;
    Vertex *v2;

    if(numOFinputFaces == 2914 && i == 8742)
    {
        std::cout<<"i : "<<i<<std::endl;
    }
    /**< Each Face has 3 vertex; vo, v1 and v2.*/
    int f0 = f->faceVertexes[0];
    int f1 = f->faceVertexes[1];
    int f2 = f->faceVertexes[2];


    v0 = inputVertex[f0];
    v1 = inputVertex[f1];
    v2 = inputVertex[f2];

    vertices[i] = Vertex(v0->getPosition(), f->getColor(), f->getNormal());
    outputData[i] = *vertices[i].getOuputData();

    vertices[i+1] = Vertex(v1->getPosition(), f->getColor(), f->getNormal());
    outputData[i+1] = *vertices[i+1].getOuputData();


    vertices[i+2] = Vertex(v2->getPosition(), f->getColor(), f->getNormal());
    outputData[i+2] = *vertices[i+2].getOuputData();
}


void Mesh::initMesh()
{
    int i = 0;
    int edgeId = 0;

    int faces[3];//f0, f1, f2;
    Vertex *v[3];//*v0, *v1, *v2;

    numOfVertices = numOFinputFaces * 3;

    vertices    = (Vertex*)malloc(sizeof(Vertex)* numOfVertices);
    outputData  = (Data*)malloc(sizeof(Data)* numOfVertices);

    for(std::vector<Face*>::iterator it=inputFaces.begin(); it != inputFaces.end(); ++it)
    {

        /**< Each Face has 3 vertex; vo, v1 and v2.*/
        faces[0] = (*it)->faceVertexes[0];
        faces[1] = (*it)->faceVertexes[1];
        faces[2] = (*it)->faceVertexes[2];


        v[0] = inputVertex[faces[0]];
        v[1] = inputVertex[faces[1]];
        v[2] = inputVertex[faces[2]];

        // Calculate face normals
        (*it)->setVertexes(*v[0],*v[1],*v[2]);
        (*it)->setNormal();

        HalfEdge *e0 = new HalfEdge(*it, v[0], v[2]);   //(in <- out)
        e0->id = edgeId++;
        v[0]->setHalfEdge(e0);
        edge_map[EMK(v[0]->id, v[2]->id)] = e0;         //(in <- out)


        HalfEdge *e1 = new HalfEdge(*it, v[1], v[0]);
        e1->id = edgeId++;
        v[1]->setHalfEdge(e1);
        edge_map[EMK(v[1]->id, v[0]->id)] = e1;


        HalfEdge *e2 = new HalfEdge(*it, v[2], v[1]);
        e2->id = edgeId++;
        v[2]->setHalfEdge(e2);
        edge_map[EMK(v[2]->id, v[1]->id)] = e2;

        (*it)->setHalfEdge(e0);

        hEdgeBuffer.push_back(e0);
        hEdgeBuffer.push_back(e1);
        hEdgeBuffer.push_back(e2);

        buildHalfEdgeConnections(e0,e1,e2);

        createData(i,(*it));
        i += 3;
    }

    // Loop over edges in edge_map and find its twin edge
    for(EdgeMap::const_iterator emit = edge_map.begin(); emit != edge_map.end(); emit++)
    {
        if(emit->first.first == 1 && emit->first.second == 2)
        {
            printf("ff\n");
        }
        auto search = edge_map.find(EMK(emit->first.second, emit->first.first));
        if(search != edge_map.end())
        {
            emit->second->setTwin(search->second);
            search->second->setTwin(emit->second);
        }
    }
}

