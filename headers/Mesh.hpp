//
//  Mesh.hpp
//  Mesh_Editor_Xcode
//
//  Created by Cristian Troncoso on 2/10/16.
//  Copyright © 2016 Cristian Troncoso. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <map>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <stack>


#include "Face.hpp"

#define DEBUG 3
#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
__FILE__, __LINE__, __func__, ##args)
#else
#define printf //
#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif


/*!
 * \brief   : Mesh class
 */
class Mesh
{

    
protected:
    Vertex *vertices;                   /**< Stores "all" model's vertices */
    
    Data* outputData;                   /**< Raw data from all vertices, with interleaving location, color and normals */
    
    int numOfVertices;                  /**< Total number of vertices after face parsing (ouput number of vertices) */
    
    int numOfInputVertices;             /**< Num of vertices on input file */
    int numOFinputFaces;                /**< Num of faces on input file */
    
    std::vector<Face*> inputFaces;      /**< Contains original vertices from OFF file */
    std::vector<Vertex*> inputVertex;   /**< Contains original faces from OFF file */

    
    
    typedef std::pair<int,int> EMK;     /**< Make a short name for the edge map's key, based on start and end vertex */
    
    typedef HalfEdge * EMV;             /**< Make a short name for the type stored at each edge, the edge map's value */
    
    typedef std::map<EMK,EMV> EdgeMap;  /**< Make a short name for the edge map */
    
    EdgeMap edge_map;

    
public:
    
    std::vector<HalfEdge*> hEdgeBuffer; /**< It stores all half edges data structures */
    
    /*!
     * \brief   Mesh constructor.
     */
    Mesh(std::string filename);
    /*!
     * \brief   Mesh Destructor.
     */
    ~Mesh(void);
    /*!
     * \brief   Loads OFF file and parse it. It generates inputFaces and InputVertex.
     * \param   Path to the OFF file
     */
    void loadObject(const std::string filename);
    /*!
     * \brief   It traverses the inputFaces and inputVertex vectors to generate all model's vertices
     */
    void initMesh();
    /*!
     * \brief   It generates a buffer with all vertex information, color, normals and what not.
     *          It uses the faces values (x,y,z) as a vertex id.
     */
    void createVertexBuffer();
    
    /*!
     * \brief   TODO - Draw is not implemented.
     */
    void draw();
    /*!
     * \brief   I gets the raw data buffer. The buffer that is loaded onto the gpu
     *          with interleaving position, color and normals.
     * \return  Data buffer
     */
    double* getVertexData();
    /*!
     * \brief   Returns the total number of vertices in the model
     * \Return  Number of vertices in model
     */
    int getNunOfVertices();
    /*!
     * \brief   It connects all halfedges adjacent to any given face
     */
    void buildHalfEdgeConnections(HalfEdge *e0, HalfEdge *e1, HalfEdge *e2);
    /*!
     * \brief   Split lines from input file for parsing purposes
     *          http://stackoverflow.com/questions/236129/split-a-string-in-c
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
    /*!
     * \brief   Find all faces around a vertex, al faces touching a vertex
     */
    std::vector<Face*> findFacesAroundVertex(Vertex *v);
    /*!
     * \brief   Find all edges that are entering a vertex v.
     */
    std::vector<HalfEdge*> findEdgesEnteringVertex(Vertex *vi);
    /*!
     * \brief   Find all edges leaving a vertex v.
     */
    std::vector<HalfEdge*> findEdgesLeavingVertex(Vertex *vo);
    /*!
     * \brief   Find all faces around a faces, normally 3 faces, less than 3 means is a boundary face
     */
    std::vector<Face*> findFacesAroundFace(Face *f);
    /*!
     * \brief   It populates the Data objec in each vertex, based on the face information
     *          collected from file plus normal and color assigned to each face.
     */
    void createData(int i, Face *f);
    /*!
     * \brief   Debugging
     * \TODO    move this to test.hpp
     */
    void test();
 
 
};

#endif /* Mesh_hpp */
