#include "Matrix3d.h"

Matrix3d::Matrix3d(int rows, int cols) : Matrix(rows, cols) {
    
}

void Matrix3d::initRotationZ(float theta) {   
    
    Matrix::operator()(0, 0) = cosf(theta);
    Matrix::operator()(0, 1) = sinf(theta);
    Matrix::operator()(1, 0) = -sinf(theta);
    Matrix::operator()(1, 1) = cosf(theta);
    Matrix::operator()(2, 2) = 1;
    Matrix::operator()(3, 3) = 1;
}

void Matrix3d::initRotationX(float theta) {
    Matrix::operator()(0, 0) = 1;
    Matrix::operator()(1, 1) = cosf(theta * 0.5f);
    Matrix::operator()(1, 2) = sinf(theta * 0.5f);
    Matrix::operator()(2, 1) = -sinf(theta * 0.5f);
    Matrix::operator()(2, 2) = cosf(theta * 0.5f);
    Matrix::operator()(3, 3) = 1;
}

void Matrix3d::initRotationY(float theta) {
    Matrix::operator()(0, 0) = cosf(theta);;
    Matrix::operator()(0, 2) = sinf(theta);
    Matrix::operator()(1, 1) = 1;
    Matrix::operator()(2, 0) = -sinf(theta);
    Matrix::operator()(2, 2) = cosf(theta);
    Matrix::operator()(3, 3) = 1;
}

void Matrix3d::initProjection(float aspectRatio, float fieldView, float zNear, float zFar) {
    Matrix::operator()(0, 0) = aspectRatio * fieldView;
    Matrix::operator()(1, 1) = fieldView;
    Matrix::operator()(2, 2) = zFar / (zFar - zNear);
    Matrix::operator()(3, 2) = (-zFar * zNear) / (zFar - zNear);
    Matrix::operator()(2, 3) = 1.0f;
}

void Matrix3d::initVertice(float x, float y, float z) {
    Matrix::operator()(0, 0) = x;
    Matrix::operator()(0, 1) = y;
    Matrix::operator()(0, 2) = z;
    Matrix::operator()(0, 3) = 1.0f;
}
