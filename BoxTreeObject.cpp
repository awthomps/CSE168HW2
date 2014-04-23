#include "BoxTreeObject.h"


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
