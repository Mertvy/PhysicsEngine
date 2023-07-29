//
// Created by Nicholas Weiss on 7/18/2023.
//

#ifndef PHYSICSENGINE_WORLD_H
#define PHYSICSENGINE_WORLD_H

#include "../util/Vector3D.h"
#include <vector>

struct Object{
    Vector3D* position;
    Vector3D* velocity;
    Vector3D* force;
    float mass;
    Object(Vector3D*, Vector3D*, Vector3D*, float);
    ~Object();
};

struct Circle : public Object {
    float radius;
    Circle(Vector3D* position, Vector3D* velocity, Vector3D* force, float mass, float radius);
}

struct LineSegment : public Object {
    Vector3D* start;
    Vector3D* end;
    LineSegment(Vector3D* start, Vector3D* end, Vector3D* velocity, Vector3D* force, float mass);
};

class World {
private:
    std::vector<Object*> objects;
    float dt;
public:
    World(float dt, Vector3D* gravity);

    void addObject(Object* obj);

    void removeObject(Object* obj);

    void updateObject(Object* obj, float dt);

    void update();

    void draw();

    Vector3D* gravity;
};



#endif //PHYSICSENGINE_WORLD_H
