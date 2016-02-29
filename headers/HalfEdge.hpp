//
// HalfEdge.hpp
// Mesh_editor_Xcode
//
// Created by Cristian Troncoso on 2/12/16
// Copyright @ 2016 Cristian Troncoso. All rights reserved
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
 *                           <-- half-edge --
 *               End* .--------------------------. *Start
 *                       .      -- twin -->     .
 *                         .                 .
 *                           .    Face     .
 *                      next    .        . prev
 *                                 .   .
 *                                   .
 */
class HalfEdge
{
private:
    HalfEdge * prev;
    HalfEdge * next;
    HalfEdge * twin;
    Face     * face;
    Vertex   * start;
    Vertex   * end;
  
public:
    int id;
    /*!
     * \Brief   : Constructor - Default.
     */
    HalfEdge();
    /*!
     * \ Brief  : Constructor, Instantiates using a face, a start vertex (half-edge origin),
     *            and a target vertex (end vertex).
     */
    HalfEdge(Face * f, Vertex * startVer, Vertex * endVer);
    /*!
     * \Brief   : Destructor.
     */
    ~HalfEdge();
    /*!
     * \Brief   : Sets a pointer to the next half-edge.
     */
    void setNext(HalfEdge * next);
    /*!
     * \Brief   : Sets a pointer to the previous half-edge.
     */
    void setPrev(HalfEdge * prev);
    /*!
     * \Brief   : Sets a pointer to the twin half-edge (the other side of the edge).
     */
    void setTwin(HalfEdge * twin);
    /*!
     * \Brief   : Sets a pointer to the target vertex.
     */
    void setEndVertex(Vertex *e);
    /*!
     * \Brief   : Sets a pointer to the origin vertex.
     */
    void setStartVertex(Vertex *s);
    /*!
     * \Brief   : Sets a pointer to the associated face.
     */
    void setFace(Face *f);
    /*!
     * \Brief   : Returns a pointer to the next half-edge.
     */
    HalfEdge * getNext();
    /*!
     * \Brief   : Returns a pointer to the previous half-edge.
     */
    HalfEdge * getPrev();
    /*!
     * \Brief   : Returns a pointer to the twin half-edge.
     */
    HalfEdge * getTwin();
    /*!
     * \Brief   : Returns a pointer to the associated face.
     */
    Face     * getFace();
    /*!
     * \Brief   : Returns a pointer to the vertex at the origin of the half-edge.
     */
    Vertex   * getStartVertex();
    /*!
     * \Brief   : Returns a pointer to the target vertex.
     */
    Vertex   * getEndVertex();
    
    //TODO
    //bool operator<(const HalfEdge& x) const;              //overloaded < operator
    //static bool comp(const HalfEdge& lhs, const HalfEdge& rhs);
};

#endif /*HalfEdge_hpp */
