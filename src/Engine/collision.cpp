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
                           pow((cir1->position->y - cir2->position->y), 2))+
                           pow((cir1->position->z - cir2->position->z), 2))*
    if (distance >= cir1->radius + cir2->radius) return;
    Vector3D* direction = new Vector3D(cir1->position->x - cir2->position->x,
                                       cir1->position->y - cir2->position->y,
                                       cir1->position->z - cir2->position->z);
    direction->scale(1/(direction->magnitude));
    cir1->force->add(direction);
    cir2->force->subtract(direction);
    delete direction;
}
/*
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
    Vector3D* slopeVec = new Vector3D(u, v, w);
    Vector3D* cirToStart = new Vector3D(line->start);
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
}*/

void circleLineCollision(Circle* cir, LineSegment* line) {
    if((line->end->x - line->start->x) != 0) {
        float m = (line->end->y - line->start->y) / (line->end->x - line->start->x);
        float c = -(line->start->y - (m * line->start->x));
        float b = 1;
        float a = -m;
        float d = fabs(a * cir->position->x + b * cir->position->y + c) / (sqrt(pow(a, 2) + pow(b, 2)));
        if (d < cir->radius) {
            cir->velocity->y = -cir->velocity->y;
        }
    }
    else {
        float d = fabs(cir->position->x - line->start->x);
        if (d < cir->radius) {
            cir->velocity->x = -cir->velocity->x;
        }
    }


}*/

void lineLineCollision(LineSegment* line1, LineSegment* line2) {
    float u = line1->end->x - line1->start->x;
    float v = line1->end->y - line1->start->y;
    float w = line1->end->z - line1->start->z;
    Vector3D* vec1 = new Vector3D(u, v, w);
    u = line2->end->x - line2->start->x;
    v = line2->end->y - line2->start->y;
    w = line2->end->z - line2->start->z;
    Vector3D* vec2 = new Vector3D(u, v, w);

}
}