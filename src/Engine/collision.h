//
// Created by Alex on 7/27/2023.
//

#ifndef PHYSICSENGINE3_COLLISION_H
#define PHYSICSENGINE3_COLLISION_H
#include <world.h>

void circleCircleCollision(Circle* cir1, Circle* cir2);

void circleLineCollision(Circle* cir, LineSegment* line);

void lineLineCollision(LineSegment* line1, LineSegment* line2);

#endif //PHYSICSENGINE3_COLLISION_H
