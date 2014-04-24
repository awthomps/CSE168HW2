#include "BoxTreeObject.h"
#include <iostream>

BoxTreeObject::BoxTreeObject()
{
	RootNode = new BoxTreeNode();
}


BoxTreeObject::~BoxTreeObject()
{
}

void BoxTreeObject::Construct(MeshObject &mesh) {
	//TODO: add the timer to check length of construction:

	Triangle** triangles = mesh.getTriangles();
	int numTriangles = mesh.getNumTriangles();
	RootNode->Contruct(numTriangles, triangles);
}

bool BoxTreeObject::Intersect(const Ray &ray, Intersection &hit) {
	float t;
	bool success = false;
	if (RootNode->TestRay(ray, t)){
		success = RootNode->Intersect(ray, hit);
		if (success) {
			std::cout << "";
		}
	}
	return success;
}