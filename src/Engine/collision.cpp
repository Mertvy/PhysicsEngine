//
// Created by Alex on 7/27/2023.
//

#include "collision.h"
#include "../util/Vector3D.h"
#include "world.h"
#include <math.h>


// check whether distance between objects is greater than sum of their radii, else apply a repulsive force
void circleCircleCollision(Circle* cir1, Circle* cir2) {
    double distance = sqrt(pow((cir1->position->x - cir2->position->x), 2) +
                           pow((cir1->position->y - cir2->position->y), 2) +
                           pow((cir1->position->z - cir2->position->z), 2));
    if (distance >= cir1->radius + cir2->radius) return;
    Vector3D* direction = new Vector3D(cir1->position->x - cir2->position->x,
                                       cir1->position->y - cir2->position->y,
                                       cir1->position->z - cir2->position->z);
    direction->scale(1/(direction->magnitude));
    cir1->force->add(direction);
    cir2->force->subtract(direction);
    delete direction;
}

void circleLineCollision(Circle* cir, LineSegment* line) {
    float u = line->end->x - line->start->x;
    float v = line->end->y - line->start->y;
    float w = line->end->z - line->start->z;
    float a = cir->position->x;
    float b = cir->position->y;
    float c = cir->position->z;
    float X = line->start->x - a;
    float Y = line->start->y - b;
    float Z = line->start->z - c;
    float square = u*u + v*v + w*w;
    float linear = X*u + Y*v + Z*w;
    float constant = X*X + Y*Y + Z*Z - cir->radius*cir->radius;
    float discriminant = linear*linear - 4 * square * constant;
    if (discriminant <= 0) return;
    float t = ((-linear) + sqrt(discriminant))/(2*square);
    if (t > 1) return;
    Vector3D* slopeVec = new Vector3D(u, v, w)
    Vector3D* cirToStart = new Vector3d(line->start);
    cirToStart->subtract(cir->position);
    float projScalar = slopeVec->dot(cirToStart)/(slopeVec->magnitude*slopeVec->magnitude);
    slopeVec->scale(projScalar);
    cirToStart->add(slopeVec);
    Vector3D* direction = cirToStart;
    direction->scale(1/(direction->magnitude));
    line->force->add(direction);
    cir->force->subtract(direction);
    delete slopeVec;
    delete cirToStart;
}

void lineLineCollision(LineSegment* line1, LineSegment* line2) {

}

}