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
    Vector3D* force = new Vector3D(cir1->position->x - cir2->position->x,
                                       cir1->position->y - cir2->position->y,
                                       cir1->position->z - cir2->position->z);
    force->scale(1/(force->magnitude));
    float forceScalar = 0.5*((1/pow((1-(overlap/cir1->radius)),1)) + (1/pow((1-(overlap/cir2->radius)),1)));
    force->scale(forceScalar);
    cir1->force->add(force);
    cir2->force->subtract(force);
    delete force;
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
    cir->velocity->scale(-1);
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
