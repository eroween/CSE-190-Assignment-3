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
//class Vector3D;
//class Matrix4;
/*!
 * \brief   Data class helps to organize the vertsx data that need
 *          to be loaded onto the GPU.
 */
class Data
{
private:
    Vector4D position;
    Vector4D color;
    Vector4D normal;
    
public:
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
    
    Vector4D getPosition()
    {
        return position;
    }

    
};

/*!
 * \brief   Containds all model's vertex information
 */
class Vertex
{
protected:
    HalfEdge *halfedge;
    Data *data;
    
public:
    int id;
  
    Vertex(){}
    
    Vertex(Vector3D position)
    {
        Vector3D color = Vector3D(0.5,0.5,0.5);
        data = new Data(position);
    }
    Vertex(Vector3D position, Vector4D color, Vector3D normal)
    {
        data = new Data(position, color, normal);
    }
    
    Vertex(Vector3D position, Vector3D normal)
    {
        Vector4D color = Vector4D(0.5,0.5,0.5,1);
        data = new Data(position, color, normal);
    }

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
    
    HalfEdge *getInHalfEdge()
    {
        return halfedge;
    }
    
};

#endif

