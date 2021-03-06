#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <list>
#include <fstream>

#include "Mesh.h"
#include "Matrix3d.h"
#include "Engine3dUtil.h"
#include <algorithm>

#define WIDTH 720
#define HEIGHT 720
#define WINDOW_TITLE "Engine 3d"
#define MAX_FPS 120.0f

LARGE_INTEGER timeFreq, timeNew, timeOld;

Mesh meshObj;

Matrix3d m(4, 4);
Matrix3d projectionMatrix(4, 4);
Matrix3d rotationXMatrix(4, 4);
Matrix3d rotationYMatrix(4, 4);
Matrix3d rotationZMatrix(4, 4);

Vertice3d camera;
Vertice3d lookDirection;
Vertice3d lightDirection = { 0.0f, 0.0f, -1.0f };

float theta;
float yaw = 0;

int keyPressed = 0;

POINT mousePosition;
LONG oldX = 0, oldY = 0;

unsigned char* readBMP(std::string filename, int& width, int& height) {
    std::ifstream file(filename);    

    unsigned char info[54];
    file.read((char*) info, 54);

    // extract image height and width from header    
    memcpy(&width, info + 18, sizeof(int));
    memcpy(&height, info + 22, sizeof(int));

    int heightSign = 1;
    if (height < 0){
        heightSign = -1;
    }

    int size = 3 * width * abs(height);
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel   
    file.read((char*) data, size);
    file.close();
 
    return data;
}

void initTexture() {
    unsigned char* data;
    GLuint idTextura;
    int width, height;
    // Comandos de inicialização para textura
    data = readBMP("imagem.bmp", width, height);
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}

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
   // meshObj.loadFromFile("mountains.obj");
   // meshObj.loadFromFile("teapot.obj");
    meshObj.loadCube();
}

void showFPS(float elapsedTime) {
    char newTitle[100];
    float fps = 1.0f / elapsedTime;
    sprintf_s(newTitle, "%s FPS: %3.2f\n", WINDOW_TITLE, fps);
    glutSetWindowTitle(newTitle);
}

void glPrintText(float x, float y, float r, float g, float b, void* font, char* string) {
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
    sprintf_s(text, "frame rate: %4.0f fps", fps);
    glPrintText(-1.0f, 0.96f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13, text);    
}

void drawLatency(float elapsedTime) {
    char text[100];
    float latency = elapsedTime * 1000.0f;
    sprintf_s(text, "frame time: %4.0f ms", latency);
    glPrintText(-1.0f, 0.92f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_8_BY_13, text);   
}

void draw(std::vector<Triangle> trianglesToDraw) {            
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);      
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   // wired model
    glBegin(GL_TRIANGLES);
    for (Triangle& triangle : trianglesToDraw) {
        glColor3f(triangle.vertices[0].r, triangle.vertices[0].g, triangle.vertices[0].b);  
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(triangle.vertices[0].x, triangle.vertices[0].y);  
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(triangle.vertices[1].x, triangle.vertices[1].y);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(triangle.vertices[2].x, triangle.vertices[2].y);
    }    
    glEnd();    
    glFlush();
}

void updateCamera(float elapsedTime) {
    Vertice3d forward = lookDirection * (4.0f * elapsedTime);

    if (GetAsyncKeyState(VK_UP)) {
        camera.y += 4.0f * elapsedTime;
    } 
    if (GetAsyncKeyState(VK_DOWN)) {
        camera.y -= 4.0f * elapsedTime;
    } 
    if (GetAsyncKeyState(VK_RIGHT)) {
        camera.x += 4.0f * elapsedTime;
    } 
    if (GetAsyncKeyState(VK_LEFT)) {
        camera.x -= 4.0f * elapsedTime;
    }
    if (GetAsyncKeyState(L'A')) {
        yaw -= 2.0f * elapsedTime;        
    }
    if (GetAsyncKeyState(L'D')) {
        yaw += 2.0f * elapsedTime;
    }
    if (GetAsyncKeyState(L'W')) {
        camera = camera + forward;
    }
    if (GetAsyncKeyState(L'S')) {        
        camera = camera - forward;       
    }
 /*   if (GetCursorPos(&mousePosition)) {
        float delta = (float)(mousePosition.x - oldX);
        if (delta != 0) {
            yaw += (1.0f / delta) * elapsedTime;
            std::cout << yaw << std::endl;
        }                
        oldX = mousePosition.x;
        oldY = mousePosition.y;
    }*/
}

std::vector<Triangle> clipScreen(std::vector<Triangle> triangles) {
    std::vector<Triangle> ret;
    for (Triangle& tri : triangles) {
        Triangle clipped[2];
        std::list<Triangle> triList;
        
        triList.push_back(tri);
        size_t newTriangles = 1;

        for (int p = 0; p < 4; p++) {
            int trisToAdd = 0;
            while (newTriangles > 0) {
                Triangle test = triList.front();
                triList.pop_front();
                newTriangles--;

                switch (p) {
                    case 0: // TOP OF SCREEN, NORMAL POINT DOWN
                        trisToAdd = test.clip({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, clipped[0], clipped[1]);
                        break;
                    case 1: // BOTTOM OF SCREEN, NORMAL POINT UP
                        trisToAdd = test.clip({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, clipped[0], clipped[1]);
                        break;
                    case 2: // LEFT OF SCREEN, NORMAL POINT RIGHT
                        trisToAdd = test.clip({ -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]);                        
                        break;
                    case 3: // RIGHT OF SCREEN, NORMAL POINT LEFT
                        trisToAdd = test.clip({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]);
                        break;
                }

                for (int w = 0; w < trisToAdd; w++) {
                    triList.push_back(clipped[w]);
                }
            }
            newTriangles = triList.size();
        }
        for (Triangle& t : triList) {            
            ret.push_back(t);
        }        
    }
    return ret;
}

void process(float elapsedTime) {
    float time = getTime();

    updateCamera(elapsedTime);

    //theta += 1.0f * elapsedTime;
    //calcRotationY(rotationYMatrix, theta);
    rotationXMatrix.initRotationX(theta);
    rotationZMatrix.initRotationZ(theta);
    Matrix rotationXZMatrix = rotationZMatrix * rotationXMatrix; // the order matters Z * X != X * Z    

    Matrix3d translation = Engine3dUtil::createTranslation(0.0f, 0.0f, 5.0f);
    Matrix world = rotationXZMatrix * translation;
    
    Vertice3d vUp = { 0.0f, 1.0f, 0.0f };
    Vertice3d vTarget = { 0.0f, 0.0f, 1.0f };

   /* yaw = 0;// -6.0f;
    Vertice3d temp(0, 0, -15);
    camera = temp - lookDirection * 10.0f;*/
    // Rotate yaw    
    Matrix3d cameraRotationMatrix(4, 4);
    cameraRotationMatrix.initRotationY(yaw);
    lookDirection = Engine3dUtil::calcProjectedVertice(vTarget, cameraRotationMatrix);
    vTarget = camera + lookDirection;

    Matrix3d cameraMatrix = Engine3dUtil::calcPointAt(camera, vTarget, vUp);
    Matrix3d viewMatrix = cameraMatrix.quickInvert();

    std::vector<Triangle> trianglesToDraw;    
    
    Vertice3d normal;
    Triangle tProjected, tTranslated, tRotatedZX, tViewed;    
    for (Triangle& triangle : meshObj.triangles) {              
        tTranslated.vertices[0] = triangle.vertices[0] * world;
        tTranslated.vertices[1] = triangle.vertices[1] * world;
        tTranslated.vertices[2] = triangle.vertices[2] * world;
        tTranslated.copyTexture(triangle);                                    

        normal = Engine3dUtil::calcNormal(tTranslated.vertices[0], tTranslated.vertices[1], tTranslated.vertices[2]);        
        if (Engine3dUtil::calcDotProduct(normal, tTranslated.vertices[0], camera) < 0.0f) {           
            float dp = std::max(0.1f, lightDirection.dotProduct(normal));            
          
            tViewed.vertices[0] = tTranslated.vertices[0] * viewMatrix;
            tViewed.vertices[1] = tTranslated.vertices[1] * viewMatrix;
            tViewed.vertices[2] = tTranslated.vertices[2] * viewMatrix;

            // clip triangles near plane
            int clippedTriangles = 0;
            Triangle clipped[2];
            clippedTriangles = tViewed.clip({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, clipped[0], clipped[1]);
            for (int n = 0; n < clippedTriangles; n++) {
                // Project 3d into 2d
                tProjected.vertices[0] = clipped[n].vertices[0] * projectionMatrix;
                tProjected.vertices[1] = clipped[n].vertices[1] * projectionMatrix;
                tProjected.vertices[2] = clipped[n].vertices[2] * projectionMatrix;  

                tProjected.copyTexture(clipped[n]);

                // Scale into view
                tProjected.vertices[0] = tProjected.vertices[0] / tProjected.vertices[0].w;
                tProjected.vertices[1] = tProjected.vertices[1] / tProjected.vertices[1].w;
                tProjected.vertices[2] = tProjected.vertices[2] / tProjected.vertices[2].w;             

                //tProjected.copyRGB(clipped[n]);
                //tProjected.setRGB(dp, dp, dp);

                trianglesToDraw.push_back(tProjected);
            }          
        }        
    }          
    
    // sort to render triangles from back to front
    sort(trianglesToDraw.begin(), trianglesToDraw.end(), [](Triangle& t1, Triangle& t2) {
        float z1 = (t1.vertices[0].z + t1.vertices[1].z + t1.vertices[2].z) / 3.0f;
        float z2 = (t2.vertices[0].z + t2.vertices[1].z + t2.vertices[2].z) / 3.0f;
        return z1 > z2;
    });   

    draw(clipScreen(trianglesToDraw));
    //draw(trianglesToDraw);   
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

void initProjectionMatrix(Matrix3d& projection) {
    float zNear = 0.1f; // min z coordinate
    float zFar = 1000.0f; // max z coordinate
    float fovDegree = 90.0f; // field of view degree
    float aRatio = (float) HEIGHT / (float) WIDTH; // aspect ratio
    float fovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f); // convert to radian
    projection.initProjection(aRatio, fovRad, zNear, zFar);
}

int main(int argc, char* argv[]) {        
    initProjectionMatrix(projectionMatrix);   
    lightDirection.normalize();

    initMesh();
    initTime();

    //GetCursorPos(&mousePosition);
    //oldX = mousePosition.x;
    //oldY = mousePosition.y;

    glutInit(&argc, argv);    
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(1, 1);
    glutCreateWindow(WINDOW_TITLE);      
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    std::cout << "Vendor        : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer      : " << glGetString(GL_RENDERER) << std::endl;

    initTexture();
    glutMainLoop();

    return EXIT_SUCCESS;
}