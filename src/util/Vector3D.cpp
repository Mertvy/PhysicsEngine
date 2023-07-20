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

    Vector3D() = default;

    float dot(Vector3D* v) {
        return this->x * v->x + this->y * v->y + this->z * v->z;
    }

    Vector3D* cross(Vector3D* v) {
        Vector3D* cross = new Vector3D;
        cross->x = this->y * v->z - this->z * v->y;
        cross->y = this->x * v->z - this->z * v->x;
        cross->z = this->x * v->y - this->y * v->x;
        return cross;
    }
};