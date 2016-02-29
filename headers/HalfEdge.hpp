//
// HalfEdge.hpp
// Mesh_editor_Xcode
//
// Created by Camel on 2/12/16
// Copyright @ 2016 CAmle. All rights reserved
//

#ifndef HalfEdge_hpp
#define HalfEdge_hpp

#include "Matrix4.hpp"
#include "Vertex.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"
#include "Face.hpp"
#include "Vertex.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>


class Face;
class Vertex;


/*!
 * \brief   Half edge data structure is used in the Mesh editor class.
 *          It allows faces, vertexs, and edge's look up in O(1) time.
 *          When parsing the faces buffer, three half edges will be 
 *          created per each face.
 *
 */
class HalfEdge
{
private:
    HalfEdge * prev;
    HalfEdge * next;
    HalfEdge * twin;
    Face     * face;
    Vertex   * in;
    Vertex   * out;
  
public:
    int id;
    HalfEdge(Face * f, Vertex * inVer, Vertex * outVer);
    ~HalfEdge();
    void setNext(HalfEdge * next);
    void setPrev(HalfEdge * prev);
    void setTwin(HalfEdge * opps);
    void setOutVertex(Vertex *o);
    void setInVertex(Vertex *i);
    void setFace(Face *f);
    HalfEdge * getNext();
    HalfEdge * getPrev();
    HalfEdge * getTwin();
    Face     * getFace();
    Vertex   * getInVertex();
    Vertex   * getOutVertex();    
    //bool operator<(const HalfEdge& x) const;              //overloaded < operator
    //static bool comp(const HalfEdge& lhs, const HalfEdge& rhs);
};

#endif /*HalfEdge_hpp */
