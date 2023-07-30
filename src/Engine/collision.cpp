//
// Created by Alex on 7/27/2023.
//

#include "collision.h"
#include "../util/Vector3D.h"
#include "world.h"
#include <math.h>


// check whether distance between objects is greater than sum of their radii, else apply a repulsive force
void objectCollision(Circle* cir1, Circle* cir2) {
    double distance = sqrt(pow((cir1->position->x - cir2->position->x), 2) +
                           pow((cir1->position->y - cir2->position->y), 2) +
                           pow((cir1->position->z - cir2->position->z), 2));
    if (distance >= cir1->radius + cir2->radius) return;
    Vector3D* direction = new Vector3D(cir1->position->x - cir2->position->x,
                                       cir1->position->y - cir2->position->y,
                                       cir1->position->z - cir2->position->z);
    direction->scale(1/sqrt(pow(direction->x, 2) + pow(direction->y, 2) + pow(direction->z, 2)));
    cir1->force->add(direction);
    direction->scale(-1);
    cir2->force->add(direction);
    delete direction;
}

void objectCollision(Circle* cir, LineSegment* line) {

}