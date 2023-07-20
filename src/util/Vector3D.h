//
// Created by Nicholas Weiss on 7/20/2023.
//

#ifndef PHYSICSENGINE_VECTOR3D_H
#define PHYSICSENGINE_VECTOR3D_H

class Vector3D {
private:

public:
    float x;
    float y;
    float z;
    float magnitude;

    Vector3D(float x, float y, float z);

    Vector3D();

    float dot(Vector3D* v);

    Vector3D* cross(Vector3D* v);
};

#endif //PHYSICSENGINE_VECTOR3D_H
