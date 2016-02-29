//
// Face.hpp
// Camel 2/15/2016
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
    int id;
    int faceVertexes[3];
    
    Face (int *fVertexes, Vector4D inColor)
    {
        faceVertexes[0] = fVertexes[0];
        faceVertexes[1] = fVertexes[1];
        faceVertexes[2] = fVertexes[2];
        color = Vector4D(inColor);
    }
    
    Face(Vector3D *vertices, Vector3D normal, Vector4D color)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        
        normal = Vector3D(normal);
        color = Vector4D(color);
    }
    
    Face(Vector3D *vertices, Vector3D normal)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        
        normal = Vector3D(normal);
    }
    
    Face(Vector3D *vertices)
    {
        vertexes[0] = vertices[0];
        vertexes[1] = vertices[1];
        vertexes[2] = vertices[2];
        
        normal = Vector3D(0);
    }
    ~Face(){}

    void setVertexes(Vertex A, Vertex B, Vertex C)
    {
        vertexes[0] = A;
        vertexes[1] = B;
        vertexes[2] = C;
    }
    
    
    void setNormal()
    {
        Vector3D AB = vertexes[1].getPosition() - vertexes[0].getPosition();
        Vector3D AC = vertexes[2].getPosition() - vertexes[0].getPosition();
        
        normal = normal.cross(AB,AC);
        //normal = normal->normalize();
    }
    
    void setFaceColor(float *inColor)
    {
        color[0] = inColor[0];
        color[1] = inColor[1];
        color[2] = inColor[2];
        color[3] = 1;
    }
    void setHalfEdge(HalfEdge *he)
    {
        halfEdge = he;
    }
    
    Vector3D getNormal()
    {
        return normal;
    }
    
    Vector4D getColor()
    {
        return color;
    }
    
    HalfEdge *getHalfEdge()
    {
        return halfEdge;
    }

    inline bool operator==(Face const & f) const
    {
        return id == f.id;
    }
        
    bool operator!=(Face const & f) const
    {
        return id != f.id;
    }
    
    /*
    void setFaceNormal(std::vector<float> A, std::vector<float> B, std::vector<float> C)
    {
        //float v[3];
        float AB[3] = { (B[0] - A[0]),
                        (B[1] - A[1]),
                        (B[2] - A[2]),
                        };
        
        float AC[3] = { (C[0] - A[0]),
                        (C[1] - A[1]),
                        (C[2] - A[2])
                        };
        
        normal[0] = AB[1] * AC[2] - AB[2] * AC[1];
        normal[1] = -1*(AB[0] * AC[2] - AC[0] * AB[2]);
        normal[2] = AB[0] * AC[1] - AC[0] * AB[1];
        normalizeVecotor(normal);
    }
     */
};

#endif
