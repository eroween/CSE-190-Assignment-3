//
//  Mesh.hpp
//  Mesh_Editor_Xcode
//
//  Created by Camel on 2/10/16.
//  Copyright © 2016 Camel. All rights reserved.
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

#define DEBUG 0
#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
__FILE__, __LINE__, __func__, ##args)
#else
#define printf //
#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif




/*!
 * \brief   Mesh class
 */
class Mesh
{

    
protected:
    Vertex *vertices;                   /**< Stores "all" model's vertices */
    
    Data* outputData;                   /**< Vertex array with interleaving location, colors and normals data  */
    
    int numOfVertices;                  /**< Total number of vertices after face parsing (ouput number of vertices) */
    
    int numOfInputVertices;
    int numOFinputFaces;
    
    std::vector<Face*> inputFaces;      /**< Contains originls vertices from OFF file */
    std::vector<Vertex*> inputVertex;   /**< Faces from OFF file */

    
    
    typedef std::pair<int,int> EMK;     /**< Make a short name for the edge map's key */
    
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
     * \brief   It traverses the inputFaces and inputVertex vector to generate all model's vertices
     */
    void initMesh();
    /*!
     * \brief   It generates a buffer with all vertex information, color, normals and what not.
     *          It used the faces values (x,y,z) as a vertex id.
     */
    void createVertexBuffer();
    
    /*!
     * \brief   TODO.
     */
    void draw();
    /*!
     * \brief   I gets the raw data buffer. The buffer that is loaded to gpu with
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
    void createHalfEdgeConnections(HalfEdge *e0, HalfEdge *e1, HalfEdge *e2);
    
    /* 
     * \brief   http://stackoverflow.com/questions/236129/split-a-string-in-c 
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);

    std::vector<Face*> findFacesAroundVertex(Vertex *v);
    
    std::vector<HalfEdge*> findEdgesIN(Vertex *vi);
    std::vector<HalfEdge*> findEdgesOUT(Vertex *vo);
    std::vector<Face*> findFacesAroundFace(Face *f);
    
    void createData(int i, Face *f);
    void test(int i , int j);
 
 
};

#endif /* Mesh_hpp */
