#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

#include "Mesh.h"
#include "Matrix.h"
#include "Engine3dUtil.h"
#include <algorithm>

#define WIDTH 1280
#define HEIGHT 720
#define WINDOW_TITLE "Engine 3d"
#define MAX_FPS 120.0f

LARGE_INTEGER timeFreq, timeNew, timeOld;

Mesh meshObj;
Matrix projectionMatrix(4, 4);
Matrix rotationXMatrix(4, 4);
Matrix rotationYMatrix(4, 4);
Matrix rotationZMatrix(4, 4);
Matrix* rotationXZMatrix;
Vertice3d camera;
Vertice3d lightDirection = { 0.0f, 0.0f, -1.0f };

float theta;

void initTime() {
    QueryPerformanceFrequency(&timeFreq);
    QueryPerformanceCounter(&timeOld);
    QueryPerformanceCounter(&timeNew);
}

float getTime() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return (float)((time.QuadPart) / (double)timeFreq.QuadPart);
}

void initMesh() {
    meshObj.loadFromFile("teapot.obj");
    //meshObj.loadCube();
}

void calcProjectedVertice(Vertice3d& in, Vertice3d& out, Matrix* projection) {
    Matrix vertice(1, 4);
    Matrix* projected;

    Engine3dUtil::initVertice(vertice, in.x, in.y, in.z);
    projected = vertice * (*projection);   

    out.x = (*projected)(0, 0);
    out.y = (*projected)(0, 1);
    out.z = (*projected)(0, 2);

    float w = (*projected)(0, 3);

    if (w != 0) {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }
    delete projected;
}

void calcRotationZ(Matrix& rotation, float theta) {
    rotation(0, 0) = cosf(theta);
    rotation(0, 1) = sinf(theta);
    rotation(1, 0) = -sinf(theta);
    rotation(1, 1) = cosf(theta);
    rotation(2, 2) = 1;
    rotation(3, 3) = 1;
}

void calcRotationX(Matrix& rotation, float theta) {
    rotation(0, 0) = 1;
    rotation(1, 1) = cosf(theta * 0.5f);
    rotation(1, 2) = sinf(theta * 0.5f);
    rotation(2, 1) = -sinf(theta * 0.5f);
    rotation(2, 2) = cosf(theta * 0.5f);
    rotation(3, 3) = 1;
}

void calcRotationY(Matrix& rotation, float theta) {
    rotation(0, 0) = cosf(theta);;
    rotation(0, 2) = sinf(theta);
    rotation(1, 1) = 1;
    rotation(2, 0) = -sinf(theta);
    rotation(2, 2) = cosf(theta);
    rotation(3, 3) = 1;
}

void showFPS(float elapsedTime) {
    char newTitle[100];
    float fps = 1.0f / elapsedTime;
    sprintf_s(newTitle, "%s FPS: %3.2f\n", WINDOW_TITLE, fps);
    glutSetWindowTitle(newTitle);
}

void glPrintText(float x, float y, float r, float g, float b, void* font, char* string)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void drawFPS(float elapsedTime) {
    char text[100];
    float fps = 1.0f / elapsedTime;
    sprintf_s(text, "FPS:     %4.0f", fps);
    glPrintText(-1.0f, 0.96f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13, text);    
}

void drawLatency(float elapsedTime) {
    char text[100];
    float latency = elapsedTime * 1000.0f;
    sprintf_s(text, "Latency: %4.0f ms", latency);
    glPrintText(-1.0f, 0.92f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13, text);   
}

void draw(std::vector<Triangle> trianglesToDraw) {            
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);      
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   // wired model
    glBegin(GL_TRIANGLES);
    for (Triangle& triangle : trianglesToDraw) {
        glColor3f(triangle.vertices[0].r, triangle.vertices[0].g, triangle.vertices[0].b);
        glVertex2f(triangle.vertices[0].x, triangle.vertices[0].y);
        glVertex2f(triangle.vertices[1].x, triangle.vertices[1].y);
        glVertex2f(triangle.vertices[2].x, triangle.vertices[2].y);
    }    
    glEnd();    
    glFlush();
}

void process(float elapsedTime) {
    float time = getTime();
    theta += 1.0f * elapsedTime;
    //calcRotationY(rotationYMatrix, theta);
    calcRotationX(rotationXMatrix, theta);
    calcRotationZ(rotationZMatrix, theta);
    rotationXZMatrix = rotationZMatrix * rotationXMatrix; // the order matters Z * X != X * Z    

    std::vector<Triangle> trianglesToDraw;
    Triangle tProjected, tTranslated, tRotatedZ, tRotatedZX;
    Vertice3d* normal;   
    
    for (Triangle& triangle : meshObj.triangles) {

        calcProjectedVertice(triangle.vertices[0], tRotatedZX.vertices[0], rotationXZMatrix);
        calcProjectedVertice(triangle.vertices[1], tRotatedZX.vertices[1], rotationXZMatrix);
        calcProjectedVertice(triangle.vertices[2], tRotatedZX.vertices[2], rotationXZMatrix);

       /* calcProjectedVertice(tRotatedZ.vertices[0], tRotatedZX.vertices[0], &rotationXMatrix);
        calcProjectedVertice(tRotatedZ.vertices[1], tRotatedZX.vertices[1], &rotationXMatrix);
        calcProjectedVertice(tRotatedZ.vertices[2], tRotatedZX.vertices[2], &rotationXMatrix); */      
             
        tTranslated = tRotatedZX;
        tTranslated.vertices[0].z = tTranslated.vertices[0].z + 8.0f;
        tTranslated.vertices[1].z = tTranslated.vertices[1].z + 8.0f;
        tTranslated.vertices[2].z = tTranslated.vertices[2].z + 8.0f;

        normal = Engine3dUtil::calcNormal(tTranslated.vertices[0], tTranslated.vertices[1], tTranslated.vertices[2]);
        if (Engine3dUtil::calcDotProduct(*normal, tTranslated.vertices[0], camera) < 0.0f) {           
            float dp = normal->dotProduct(lightDirection);

            calcProjectedVertice(tTranslated.vertices[0], tProjected.vertices[0], &projectionMatrix);
            calcProjectedVertice(tTranslated.vertices[1], tProjected.vertices[1], &projectionMatrix);
            calcProjectedVertice(tTranslated.vertices[2], tProjected.vertices[2], &projectionMatrix);
            
            tProjected.setRGB(dp, dp, dp);
            trianglesToDraw.push_back(tProjected); 
        }
        delete normal;
    }      
    delete rotationXZMatrix;
    
    // sort to render triangles from back to front
    sort(trianglesToDraw.begin(), trianglesToDraw.end(), [](Triangle& t1, Triangle& t2) {
        float z1 = (t1.vertices[0].z + t1.vertices[1].z + t1.vertices[2].z) / 3.0f;
        float z2 = (t2.vertices[0].z + t2.vertices[1].z + t2.vertices[2].z) / 3.0f;
        return z1 > z2;
    });   
    
    draw(trianglesToDraw);   
    time = getTime() - time;
    drawLatency(time);
    drawFPS(elapsedTime);
    glFlush();
}

void display() {        
    
}

void idle() {
    QueryPerformanceCounter(&timeNew);
    float elapsedTime = (float) ((timeNew.QuadPart - timeOld.QuadPart) / (double) timeFreq.QuadPart);    

    if (elapsedTime >= (1.0f / MAX_FPS)) {        
        timeOld = timeNew;
        process(elapsedTime);        
    }
}

void initProjectionMatrix(Matrix& projection) {
    float zNear = 0.1f; // min z coordinate
    float zFar = 1000.0f; // max z coordinate
    float fovDegree = 90.0f; // field of view degree
    float aRatio = (float) HEIGHT / (float) WIDTH; // aspect ratio
    float fovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f); // convert to radian
    Engine3dUtil::initProjection(projection, aRatio, fovRad, zNear, zFar);
}

int main(int argc, char* argv[]) {       
    initProjectionMatrix(projectionMatrix);   
    lightDirection.normalize();

    initMesh();
    initTime();

    glutInit(&argc, argv);    
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1, 1);
    glutCreateWindow(WINDOW_TITLE);      
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    std::cout << "Vendor        : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer      : " << glGetString(GL_RENDERER) << std::endl;

    glutMainLoop();

    return EXIT_SUCCESS;
}