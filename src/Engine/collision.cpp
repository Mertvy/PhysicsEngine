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
    float overlap = cir1->radius + cir2->radius - distance;
    if (overlap < 0) return;

    Vector3D* direction = new Vector3D(cir2->position);
    direction->subtract(cir1->position);
    direction->scale(1/direction->magnitude);
    Vector3D* velDiff = new Vector3D(cir1->velocity);
    velDiff->subtract(cir2->velocity);
    float impulse = 2*((direction->dot(velDiff))/((1/cir1->mass) + (1/cir2->mass)));
    Vector3D* dVel1 = new Vector3D(direction);
    Vector3D* dVel2 = new Vector3D(direction);
    dVel1->scale(-impulse/cir1->mass);
    dVel2->scale(impulse/cir2->mass);
    cir1->velocity->add(dVel1);
    cir2->velocity->add(dVel2);

    delete direction;
    delete velDiff;
    delete dVel1;
    delete dVel2;
}



void circleLineCollision(Circle* cir, LineSegment* line) {
    // substituting line equation into circle equation then check for solution
    // line defined by <u, v, w>t + <a, b, c>
    float u = line->end->x - line->start->x;
    float v = line->end->y - line->start->y;
    float w = line->end->z - line->start->z;
    float a = line->start->x - cir->position->x;
    float b = line->start->y - cir->position->y;
    float c = line->start->z - cir->position->z;
    // quadratic of form Ax^2+Bx+C=0
    float A = u*u + v*v + w*w;
    float B = 2*(u*a + v*b + w*c);
    float C = a*a + b*b + c*c - cir->radius*cir->radius;
    float discriminant = sqrt(B*B-4*A*C);
    if (discriminant < 0) return;
    float t1 = (0-B-discriminant)/(2*A);
    float t2 = (0-B+discriminant)/(2*A);
    if (!((t1 > 0 && t1 < 1) || (t2 > 0 && t2 < 1))) return;

    // reflect velocity over line
    Vector3D* projection = new Vector3D(u, v, w);
    float projectionScalar = (projection->dot(cir->velocity))/pow(projection->magnitude, 2);
    projection->scale(projectionScalar);
    Vector3D* newVel = new Vector3D(projection);
    newVel->scale(2);
    newVel->subtract(cir->velocity);
    Vector3D* oldVel = cir->velocity;
    cir->velocity = newVel;
    delete oldVel;
    delete projection;
}
/*
void circleLineCollision(Circle* cir, LineSegment* line) {
    if((line->end->x - line->start->x) != 0) {
        float m = (line->end->y - line->start->y) / (line->end->x - line->start->x);
        float c = -(line->start->y - (m * line->start->x));
        float a = -m;
        float d = fabs(a * cir->position->x + cir->position->y + c) / (sqrt(pow(a, 2) + 1));

        float b1 = (line->start->y - m* line->start->x);
        float b2 = (cir->position->y - (-1/m) * cir->position->x);
        float x = (b2-b1)/(m+(1/m));
        float y = m*x + b1;
        if(x > line->end->x || x < line->start->x) return;
        if(y > line->end->y || y < line->start->y) return;

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


}
*/

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
