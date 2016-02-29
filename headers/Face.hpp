//
// Face.hpp
// Cristian Troncoso 2/15/2016
//

#ifndef Face_hpp
#define Face_hpp
#include <cmath>
#include "Vertex.hpp"

/*!
 * \brief   Containds all model's faces information
 */
class Face
{
    
protected:
    HalfEdge *halfEdge = NULL;

    Vector3D normal;
    Vector4D color;
    Vertex vertexes[3];
    
    
public:
    int id;                                     /**< The id is the input order according to the input file */
    int faceVertexes[3];                        /**< Vertex index according to the input file */
    
    /*!
     * \Brief   : Constructor, default.
     */
    Face(){}
    /*!
     * \Brief   : Constructor,Initializes a Face bases on Vertex index (from input file) and color.
     */
    Face (int *fVertexes, Vector4D inColor)
    {
        faceVertexes[0] = fVertexes[0];
        faceVertexes[1] = fVertexes[1];
        faceVertexes[2] = fVertexes[2];
        color = Vector4D(inColor);
    }
    /*!
     * \Brief   : Constructor, Initializes using position, normal and color.
     */
    Face(Vector3D *vertices, Vector3D normal, Vector4D color)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        
        normal = Vector3D(normal);
        color = Vector4D(color);
    }
    /*!
     * \Brief   : Constructor, Initializes using position and normal.
     */
    Face(Vector3D *vertices, Vector3D normal)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        normal = Vector3D(normal);
    }
    /*!
     * \Brief   : Constructor, Initialize using position.
     */
    Face(Vector3D *vertices)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        
        normal = Vector3D(0);
    }
    /*!
     * \Brief   : Destructor.
     */
    ~Face(){}
    /*!
     * \Brief   : Instantiates the Vertexes class in this Face
     */
    void setVertexes(Vertex A, Vertex B, Vertex C)
    {
        vertexes[0] = A;
        vertexes[1] = B;
        vertexes[2] = C;
    }
    /*!
     * \Brief   : Calculates an set the Face's normal.
     */
    void setNormal()
    {
        Vector3D AB = vertexes[1].getPosition() - vertexes[0].getPosition();
        Vector3D AC = vertexes[2].getPosition() - vertexes[0].getPosition();
        
        normal = normal.cross(AB,AC);
        //normal = normal->normalize();
    }
    /*!
     * \Brief   : Sets the face's color.
     */
    void setFaceColor(float *inColor)
    {
        color[0] = inColor[0];
        color[1] = inColor[1];
        color[2] = inColor[2];
        color[3] = 1;
    }
    /*!
     * \Brief   : Sets the default half-edge.
     */
    void setHalfEdge(HalfEdge *he)
    {
        halfEdge = he;
    }
    /*!
     * \Brief   : Return face's normal vector.
     */
    Vector3D getNormal()
    {
        return normal;
    }
    /*!
     * \Brief   : Return the face's color.
     */
    Vector4D getColor()
    {
        return color;
    }
    /*!
     * \Brief   : Return the default half-edge associates with this face.
     */
    HalfEdge *getHalfEdge()
    {
        return halfEdge;
    }
    /*!
     * \Brief   : Check if this edge is in the boundary of the Mesh (Manifold checking)
     */
    bool isBoundary()
    {
        //TODO
        return false;
    }
    //TODO
    inline bool operator==(Face const & f) const
    {
        return id == f.id;
    }
    bool operator!=(Face const & f) const
    {
        return id != f.id;
    }
    
};

#endif
