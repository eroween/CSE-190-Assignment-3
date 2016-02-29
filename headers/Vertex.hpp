//
// Vertex.hpp
//
// Created by Camel 2/15/2016
//

#ifndef Vertex_hpp
#define Vertex_hpp

#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "HalfEdge.hpp"
#include "Vector3D.hpp"

class HalfEdge;

/*!
 * \brief   Data class helps to organize the Vertexe data that needs
 *          to be loaded onto the GPU.
 */
class Data
{
private:
    Vector4D position;              /**< (x,y,z,1) position. */
    Vector4D color;
    Vector4D normal;
    
public:
    /*!
     * \Brief   : Constructor, instantiates using Vetex's position.
     */
    Data(Vector3D p)
    {
        position[0] = p[0];
        position[1] = p[1];
        position[2] = p[2];
        position[3] = 1;
        
        color[0] = 0.5;
        color[1] = 0.5;
        color[2] = 0.5;
        color[3] = 1;
        
        normal[0] = 0;
        normal[1] = 0;
        normal[2] = 0;
        normal[3] = 1;
    }
    /*!
     * \Brief   : Constructor, instantiates using Vetex's position, color and normal.
     */
    Data(Vector3D p, Vector4D c, Vector3D n)
    {
        position[0] = p[0];
        position[1] = p[1];
        position[2] = p[2];
        position[3] = 1;
        
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        color[3] = c[3];
        
        normal[0] = n[0];
        normal[1] = n[1];
        normal[2] = n[2];
        normal[3] = 1;
    }
    /*!
     * \Brief   : Returns the position vector, used by VErtex class.
     */
    Vector4D getPosition()
    {
        return position;
    }
}; //End Class Data

/*!
 * \brief   Containds all model's vertex information
 */
class Vertex
{
protected:
    HalfEdge *halfedge;
    Data *data;                     /**< Contains the raw data (position, color and normal). */
    
public:
    int id;                         /**< Identify the vertices based on input order (Index). */
    /*!
     * \Brief   : Default constructor.
     */
    Vertex(){}
    /*!
     * \Brief   : Constructor, Initializes Vertex using position vector.
     */
    Vertex(Vector3D position)
    {
        Vector3D color = Vector3D(0.5,0.5,0.5);
        data = new Data(position);
    }
    /*!
     * \Brief   : Constructor, Initializes Vertex using position, color and normal vectors.
     */
    Vertex(Vector3D position, Vector4D color, Vector3D normal)
    {
        data = new Data(position, color, normal);
    }
    /*!
     * \Brief   : Constructor, Initializes Vertex using position and normal vectors.
     */
    Vertex(Vector3D position, Vector3D normal)
    {
        Vector4D color = Vector4D(0.5,0.5,0.5,1);
        data = new Data(position, color, normal);
    }
    /*!
     * \Brief   : Destructor.
     */
    ~Vertex(){}
    
    Vector3D getPosition()
    {
        Vector4D position(data->getPosition());
        return position.toVector3D();
    }

    Data* getOuputData()
    {
        return data;
    }
    
    void setHalfEdge(HalfEdge* he)
    {
        halfedge = he;
    }
    
    HalfEdge *getHalfEdge()
    {
        return halfedge;
    }
    
};

#endif

