////////////////////////////////////////
// Object.h
////////////////////////////////////////

#ifndef CSE168_OBJECT_H
#define CSE168_OBJECT_H

#include "Ray.h"
#include "Intersection.h"

////////////////////////////////////////////////////////////////////////////////

class Object {
public:
	virtual ~Object()	{}
	virtual bool Intersect(const Ray &ray, Intersection &hit)=0;
};

////////////////////////////////////////////////////////////////////////////////

#endif