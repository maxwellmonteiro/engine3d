#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

#include "structs.h"
#include "Matrix.h"

#define WIDTH 1280
#define HEIGHT 720
#define WINDOW_TITLE "Engine 3d"
#define MAX_FPS 120.0f

LARGE_INTEGER timeFreq, timeNew, timeOld;

mesh meshObj;
Matrix* projectionMatrix;
Matrix* rotationXMatrix;
Matrix* rotationZMatrix;
Matrix* rotationXZMatrix;
float theta;

void initTime() {
    QueryPerformanceFrequency(&timeFreq);
    QueryPerformanceCounter(&timeOld);
    QueryPerformanceCounter(&timeNew);
}

void initMesh() {
    meshObj.triangles = {

        // SOUTH
        { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        // EAST                                                      
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

        // NORTH                                                     
        { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

        // WEST                                                      
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

        // TOP                                                       
        { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

        // BOTTOM                                                    
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f }
        
    };
}

void calcProjectedVertice(vertice3d& in, vertice3d& out, Matrix* projection) {
    Matrix* vertice;
    Matrix* projected;

    vertice = Matrix::getVertice(in.x, in.y, in.z);
    projected = (*vertice) * (*projection);

    out.x = projected->matrix[0][0];
    out.y = projected->matrix[0][1];
    out.z = projected->matrix[0][2];

    float w = projected->matrix[0][3];

    if (w != 0) {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }
    delete vertice;
    delete projected;
}

void calcRotationZ(Matrix* rotation, float theta) {
    rotation->matrix[0][0] = cosf(theta);
    rotation->matrix[0][1] = sinf(theta);
    rotation->matrix[1][0] = -sinf(theta);
    rotation->matrix[1][1] = cosf(theta);
    rotation->matrix[2][2] = 1;
    rotation->matrix[3][3] = 1;
}

void calcRotationX(Matrix* rotation, float theta) {
    rotation->matrix[0][0] = 1;
    rotation->matrix[1][1] = cosf(theta * 0.5f);
    rotation->matrix[1][2] = sinf(theta * 0.5f);
    rotation->matrix[2][1] = -sinf(theta * 0.5f);
    rotation->matrix[2][2] = cosf(theta * 0.5f);
    rotation->matrix[3][3] = 1;
}

void showFPS(float elapsedTime) {
    char newTitle[255];
    float fps = 1.0f / elapsedTime;
    sprintf_s(newTitle, "%s FPS: %3.2f\n", WINDOW_TITLE, fps);
    glutSetWindowTitle(newTitle);
}

void draw(float elapsedTime) {
    glClearColor(0, 0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT);    

    theta += 1.0f * elapsedTime;
    calcRotationX(rotationXMatrix, theta);
    calcRotationZ(rotationZMatrix, theta);
    rotationXZMatrix = (*rotationXMatrix) * (*rotationZMatrix);

    triangle tProjected, tTranslated, tRotatedZ, tRotatedZX;
    for (auto triangle : meshObj.triangles) {

        calcProjectedVertice(triangle.vertices[0], tRotatedZX.vertices[0], rotationXZMatrix);
        calcProjectedVertice(triangle.vertices[1], tRotatedZX.vertices[1], rotationXZMatrix);
        calcProjectedVertice(triangle.vertices[2], tRotatedZX.vertices[2], rotationXZMatrix);

     /*   calcProjectedVertice(tRotatedZ.vertices[0], tRotatedZX.vertices[0], rotationXMatrix);
        calcProjectedVertice(tRotatedZ.vertices[1], tRotatedZX.vertices[1], rotationXMatrix);
        calcProjectedVertice(tRotatedZ.vertices[2], tRotatedZX.vertices[2], rotationXMatrix);       */
             
        tTranslated = tRotatedZX;
        tTranslated.vertices[0].z = tRotatedZX.vertices[0].z + 3.0f;
        tTranslated.vertices[1].z = tRotatedZX.vertices[1].z + 3.0f;
        tTranslated.vertices[2].z = tRotatedZX.vertices[2].z + 3.0f;       

        calcProjectedVertice(tTranslated.vertices[0], tProjected.vertices[0], projectionMatrix);
        calcProjectedVertice(tTranslated.vertices[1], tProjected.vertices[1], projectionMatrix);
        calcProjectedVertice(tTranslated.vertices[2], tProjected.vertices[2], projectionMatrix);
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);        
        glVertex2f(tProjected.vertices[0].x, tProjected.vertices[0].y);
        glVertex2f(tProjected.vertices[1].x, tProjected.vertices[1].y);
        glVertex2f(tProjected.vertices[2].x, tProjected.vertices[2].y);
        glEnd();     

       /* glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(tProjected.vertices[0].x, tProjected.vertices[0].y);
        glVertex2f(tProjected.vertices[1].x, tProjected.vertices[1].y);
        glVertex2f(tProjected.vertices[2].x, tProjected.vertices[2].y);
        glEnd();*/
    }      
    delete rotationXZMatrix;

    glFlush();
}

void display() {        
    
}

void idle() {
    QueryPerformanceCounter(&timeNew);
    float elapsedTime = (float) ((timeNew.QuadPart - timeOld.QuadPart) / (double) timeFreq.QuadPart);    

    if (elapsedTime >= (1.0f / MAX_FPS)) {        
        timeOld = timeNew;
        draw(elapsedTime);
        showFPS(elapsedTime);
    }
}

Matrix* initProjectionMatrix() {
    float zNear = 0.1f; // min z coordinate
    float zFar = 1000.0f; // max z coordinate
    float fovDegree = 90.0f; // field of view degree
    float aRatio = (float) HEIGHT / (float) WIDTH; // aspect ratio
    float fovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f); // convert to radian
    return Matrix::getProjection(aRatio, fovRad, zNear, zFar);
}

int main(int argc, char* argv[]) {
    projectionMatrix = initProjectionMatrix();
    rotationXMatrix = new Matrix(4, 4);
    rotationZMatrix = new Matrix(4, 4);    
    rotationXMatrix->init();
    rotationZMatrix->init();

    initMesh();
    initTime();

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1, 1);
    glutCreateWindow(WINDOW_TITLE);   
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    delete projectionMatrix;
    delete rotationXMatrix;
    delete rotationZMatrix;    

    return EXIT_SUCCESS;
}