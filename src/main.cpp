#include "MY_GLSL.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Mesh.hpp"
#include "HalfEdge.hpp"
#include "Vertex.hpp"
#include "test.hpp"

GLuint	vboHandle[1];	// a VBO that contains interleaved positions and colors
GLuint programObject;

Mesh *mesh;

// GLUT motion variables
#define XFORM_NONE    0
#define XFORM_ROTATE  1
#define XFORM_SCALE 2

int xform_mode = 0;

int press_x, press_y;
float x_angle = 0.0; //-1
float y_angle = 0.0;
float scale_size = 1;
glm::vec3 translate;

// Initialize the VBO
void InitVBO()
{
    glGenBuffers(1, vboHandle);   // create an interleaved VBO object
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);   // bind the first handle

    glBufferData(GL_ARRAY_BUFFER, sizeof(Data)*(mesh->getNunOfVertices()), (GLdouble*)(mesh->getVertexData()), GL_STATIC_DRAW);


    /**
     * This chunk of code here is to prepare the index buffer -
     * Not needed so far since I am using an Array buffer rather than vertex buffer
     */
    /*
     glGenBuffers(1, &indexVBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*(numOfVertices), tindices, GL_STATIC_DRAW);//!<  We moved the position
     //!< and color data over to the graphics card. There will be no redundant data copy at drawing time */

}

// Display
void display()
{

    glEnable(GL_DEPTH_TEST);    // need depth test to correctly draw 3D objects
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programObject);


    GLuint c0=glGetAttribLocation(programObject, "vertex_position");
    GLuint c1=glGetAttribLocation(programObject, "vertex_color");
    GLuint c2=glGetAttribLocation(programObject, "vertex_normal");

    glVertexAttribPointer(c0,4,GL_DOUBLE, GL_FALSE, 12*sizeof(GLdouble),(GLvoid*)0);//(char*) NULL+0
    glVertexAttribPointer(c1,4,GL_DOUBLE, GL_FALSE, 12*sizeof(GLdouble),(GLvoid*)(4*sizeof(GLdouble)));//(char*) NULL+16
    glVertexAttribPointer(c2,4,GL_DOUBLE, GL_FALSE, 12*sizeof(GLdouble),(GLvoid*)(8*sizeof(GLdouble)));//(char*) NULL+24

    glEnableVertexAttribArray(c0);
    glEnableVertexAttribArray(c1);
    glEnableVertexAttribArray(c2);
    /**
     * This chunk of code here is to prepare the index buffer -
     * Not needed so far since I am using an Array buffer rather than vertex buffer
     */
    //glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    //Tells OpenGL how to walk through the VBOs, i.e., how the data are packed
    //number of coordinates per vertex (4 here), type of the coordinates,
    //stride between consecutive vertices, and pointers to the first coordinate


    GLint viewLoc = glGetUniformLocation(programObject, "view");
    GLint projLoc = glGetUniformLocation(programObject, "projection");
    GLint modelLoc = glGetUniformLocation(programObject, "model");

    glm::mat4 projection = glm::perspective(45.0f,1.0f,.1f,100.0f);

    /*

    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 20.0, 30.0),
                                 glm::vec3(0.0, 0.0, 0.0),
                                 glm::vec3(0.0, 5.0, .0));
    */
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 15.0),
                                 glm::vec3(0.0, 0.0, 0.0),
                                 glm::vec3(0.0, -1.0, 0.0));

    glm::mat4 model;
    model = glm::mat4(1.0f);

    model = glm::translate(model, translate);
    //model = glm::mat4(1.0f);

    model = glm::rotate(model, x_angle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, y_angle, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(scale_size));

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,  &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE,&projection[0][0]);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_BYTE, (char*) NULL+0);
    glDrawArrays(GL_TRIANGLES, 0, mesh->getNunOfVertices());



    glutSwapBuffers();
}

// GLUT user interactions
void mymouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        press_x = x; press_y = y;
        if (button == GLUT_LEFT_BUTTON)			xform_mode = XFORM_ROTATE;
        else if (button == GLUT_RIGHT_BUTTON)	xform_mode = XFORM_SCALE;
    }
    else if (state == GLUT_UP)					xform_mode = XFORM_NONE;
}

void mymotion(int x, int y)
{
    if (xform_mode==XFORM_ROTATE)
    {
        x_angle += (x - press_x)/10.0;
        if (x_angle > 180) x_angle -= 360;
        else if (x_angle <-180) x_angle += 360;
        press_x = x;

        y_angle += (y - press_y)/10.0;
        if (y_angle > 180) y_angle -= 360;
        else if (y_angle <-180) y_angle += 360;
        press_y = y;
    }
    else if (xform_mode == XFORM_SCALE)
    {
        float old_size = scale_size;
        scale_size *= (1+ (y - press_y)/60.0);
        if (scale_size <0) scale_size = old_size;
        press_y = y;
    }
    glutPostRedisplay();
}

void keyHandler(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x':
            // move cube left by a small amount
            translate.x = translate.x - 1.0;
            translate.y = 0.0;
            translate.z = 0.0;
            break;
        case 'X':
            translate.x = translate.x + 1.0;
            translate.y = 0.0;
            translate.z = 0.0;
            break;
        case 'y':
            translate.x = 0.0;
            translate.y = translate.y - 1.0;
            translate.z = 0.0;
            break;
        case 'Y':
            translate.x = 0.0;
            translate.y = translate.y + 1.0;
            translate.z = 0.0;
            break;
        case 'z':
            translate.x = 0.0;
            translate.y = 0.0;
            translate.z = translate.z - 1.0;
            break;
        case 'Z':
            translate.x = 0.0;
            translate.y = 0.0;
            translate.z = translate.z + 1.0;
            break;
        case 't':
            //mesh->collapseMesh();
            //collapse();
            InitVBO();
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

// main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(600,600);

    glutCreateWindow("shader cube");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyHandler);
    glutMouseFunc(mymouse);
    glutMotionFunc(mymotion);

    mesh = new Mesh("../models/testpatch.off");//testpatch.
    programObject = Setup_GLSL("../shaders/mesh_shader");  //create shaders
    /**< It tells OpenGl to draw the primitives as lines.*/
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Shows only the lines
    InitVBO();
    glutMainLoop();
}
