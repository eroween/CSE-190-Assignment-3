#include "MY_GLSL.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>

#include <GL/glut.h>

#include "OFFLoader.hpp"
#include "Mesh.hpp"

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

glm::mat4 projection = glm::perspective(45.0f,1.0f,.1f,100.0f);

glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 15.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0));

// Display
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUseProgram(programObject);

    mesh->bind(programObject);

    GLint viewLoc = glGetUniformLocation(programObject, "view");
    GLint projLoc = glGetUniformLocation(programObject, "projection");
    GLint modelLoc = glGetUniformLocation(programObject, "model");

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,  glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh->model()));

    std::cout << mesh->data_size() << std::endl;

    glDrawArrays(GL_TRIANGLES, 0, mesh->data_size());

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
        mesh->rotate((y - press_y) / -50.0, glm::vec3(1.0, 0.0, 0.0));
        mesh->rotate((x - press_x) / -50.0, glm::vec3(0.0, 1.0, 0.0));
        press_x = x;
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
        case 's':
            mesh->subdivide();
            break;
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

    glutCreateWindow("subdivsion-model");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyHandler);
    glutMouseFunc(mymouse);
    glutMotionFunc(mymotion);
    glewInit();

    mesh = OFFLoader::load("./models/testpatch.off");
    programObject = Setup_GLSL("./shaders/mesh_shader");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Shows only the lines
    glutMainLoop();
    return 0;
}
