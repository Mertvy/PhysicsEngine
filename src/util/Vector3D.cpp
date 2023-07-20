//
// Created by Nicholas Weiss on 7/20/2023.
//

#include "Vector3D.h"
#include "math.h"

class Vector3D {
private:

public:
    float x;
    float y;
    float z;
    float magnitude;

    Vector3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->magnitude = sqrt(x*x+y*y+z*z);
    }

    Vector3D(Vector3D* vec) {
        this->x = vec->x;
        this->y = vec->y;
        this->z = vec->z;
        this->magnitude = vec->magnitude;
    }

    Vector3D() = default;

    void scale(float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
    }

    void add(Vector3D* vec) {
        this->x += vec->x;
        this->y += vec->y;
        this->z += vec->z;
    }


    float dot(Vector3D* vec) {
        return this->x * vec->x + this->y * vec->y + this->z * vec->z;
    }

    Vector3D* cross(Vector3D* vec) {
        Vector3D* cross = new Vector3D;
        cross->x = this->y * vec->z - this->z * vec->y;
        cross->y = this->x * vec->z - this->z * vec->x;
        cross->z = this->x * vec->y - this->y * vec->x;
        return cross;
    }
};