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
/*
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
        */
    };
}

void showFPS(float elapsedTime) {
    char newTitle[255];
    float fps = 1.0f / elapsedTime;
    sprintf_s(newTitle, "%s FPS: %3.2f\n", WINDOW_TITLE, fps);
    glutSetWindowTitle(newTitle);
}

void draw() {
    glClearColor(0, 0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);

    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(0, 1);

    glEnd();

    glFlush();
}

void display() {        
    
}

void idle() {
    QueryPerformanceCounter(&timeNew);
    float elapsedTime = (float) ((timeNew.QuadPart - timeOld.QuadPart) / (double) timeFreq.QuadPart);    

    if (elapsedTime >= (1.0f / MAX_FPS)) {        
        timeOld = timeNew;
        draw();
        showFPS(elapsedTime);
    }
}

int main(int argc, char* argv[]) {
    Matrix a(2, 3);
    Matrix b(3, 2);
    Matrix* c;
    a.matrix[0][0] = 1;
    a.matrix[0][1] = 2;
    a.matrix[0][2] = 3;
    a.matrix[1][0] = -2;
    a.matrix[1][1] = 0;
    a.matrix[1][2] = 4;

    b.matrix[0][0] = 2;
    b.matrix[0][1] = 3;
    b.matrix[1][0] = 0;
    b.matrix[1][1] = 1;
    b.matrix[2][0] = -1;
    b.matrix[2][1] = 4;

    c = a * b;
    c->print();
    delete c;

    initTime();
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1, 1);

    glutCreateWindow(WINDOW_TITLE);   

    glutDisplayFunc(display);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}