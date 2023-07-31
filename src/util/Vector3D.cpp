//
// Created by Nicholas Weiss on 7/20/2023.
//

#include "Vector3D.h"
#include "math.h"

Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->magnitude = sqrt(x*x+y*y+z*z);
}

Vector3D::Vector3D(Vector3D* vec) {
    this->x = vec->x;
    this->y = vec->y;
    this->z = vec->z;
    this->magnitude = vec->magnitude;
}

Vector3D::Vector3D() = default;

void Vector3D::scale(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

void Vector3D::add(Vector3D* vec) {
    this->x += vec->x;
    this->y += vec->y;
    this->z += vec->z;
    this->magnitude = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

void Vector3D::subtract(Vector3D *vec) {
    this->x -= vec->x;
    this->y -= vec->y;
    this->z -= vec->z;
    this->magnitude = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}


float Vector3D::dot(Vector3D* vec) {
    return this->x * vec->x + this->y * vec->y + this->z * vec->z;
}

Vector3D* Vector3D::cross(Vector3D* vec) {
    float crossX = this->y * vec->z - this->z * vec->y;
    float crossY = this->x * vec->z - this->z * vec->x;
    float crossZ = this->x * vec->y - this->y * vec->x;
    Vector3D* cross = new Vector3D(crossX, crossY, crossZ);
    return cross;
}