//
// Vertex.hpp
//
// Created by Cristian Troncoso 2/15/2016
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
 * \brief   Data class helps to organize the Vertex data that needs
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
     * \Brief   : Constructor, instantiates using Vetex's position, some default color
     *            and normal (0,0,0,1).
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
     * \Brief   : Set the Vertex's normal
     */
    void setNormal(Vector4D n)
    {
        normal = Vector4D(n);
    }
    /*!
     * \Brief   : Returns the vector's position,used by Vertex class.
     */
    Vector4D getPosition()
    {
        return position;
    }
}; //End Class Data

/*!
 * \brief   Class Vertex stores all information of model's vertexes.
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
    
    /*!
     * \Brief   : Set the normal vector on each Vertex.
     */
    void setNormal(Vector4D n)
    {
        data->setNormal(n);
    }
    /*!
     * \Brief   : Return the (x,y,z) position of a Vertex in space.
     */
    Vector3D getPosition()
    {
        Vector4D position(data->getPosition());
        return position.toVector3D();
    }
    /*!
     * \Brief   : Returns all Vetex data; position, color and normal. Ready to 
     *            be loaded onto GPU.
     */
    Data* getOuputData()
    {
        return data;
    }
    /*!
     * \Brief   : Set the associated half-edge
     */
    void setHalfEdge(HalfEdge* he)
    {
        halfedge = he;
    }
    /*
     * \Brief   : Return the associated half-edge.
     */
    HalfEdge *getHalfEdge()
    {
        return halfedge;
    }
    
};

#endif //End Vertex_hpp

