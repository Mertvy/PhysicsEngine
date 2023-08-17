//
// Created by Nicholas Weiss on 7/18/2023.
//

#ifndef PHYSICSENGINE_WORLD_H
#define PHYSICSENGINE_WORLD_H

#include "../util/Vector3D.h"
#include <vector>

class Object{
public: Vector3D* position;
public: Vector3D* velocity;
public: Vector3D* force;
public: float mass;
public: Object(Vector3D*, Vector3D*, Vector3D*, float);
public: ~Object();
public: virtual void collide(Object* obj) = 0;
};

class Circle : public Object {

public:
    float radius;

    Circle(Vector3D* position, Vector3D* velocity, Vector3D* force, float mass, float radius);

    void collide(Object* obj);
};

class LineSegment : public Object {

public:
    Vector3D* end;
    Vector3D* start;

    LineSegment(Vector3D* start, Vector3D* end, Vector3D* velocity, Vector3D* force, float mass);

    void collide(Object* obj);
};

class World {
private:
    float dt;
public:
    World(float dt, Vector3D* gravity);

    void addObject(Object* obj);

    void removeObject(Object* obj);

    void updateObject(Object* obj, float dt);

    void update();

    void draw();

    void airresistance();

    Vector3D* gravity;
    std::vector<Object*> objects;
};



#endif //PHYSICSENGINE_WORLD_H
