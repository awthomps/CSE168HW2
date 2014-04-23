#include "BoxTreeNode.h"


BoxTreeNode::BoxTreeNode()
{
}


BoxTreeNode::~BoxTreeNode()
{
}


bool BoxTreeNode::Intersect(const Ray &ray, Intersection &hit) {
	return false;
}


void BoxTreeNode::Contruct(int count, Triangle **tri) {
	//Compute BoxMin & BoxMax to fit around all tri's:
	//init min and max to first triangles values:
	BoxMin.x = BoxMax.x = tri[0]->GetVtx(0).Position[0];
	BoxMin.y = BoxMax.y = tri[0]->GetVtx(0).Position[1];
	BoxMin.z = BoxMax.z = tri[0]->GetVtx(0).Position[2];

	//iterate through triangles
	for (int i = 0; i < count; ++i) {
		//iterate through vertices
		for (int j = 0; j < 3; ++j) {
			//iterate through x, y, and z checking boxmin and boxmax
			for (int k = 0; k < 3; ++k) {
				if (BoxMin[k] > tri[i]->GetVtx(j).Position[k]) BoxMin[k] = tri[i]->GetVtx(j).Position[k];
				if (BoxMax[k] < tri[i]->GetVtx(j).Position[k]) BoxMax[k] = tri[i]->GetVtx(j).Position[k];
			}
		}
	}

	//check ifthis is a leaf node
	if (count <= MAXTRIANGLESPERBOX) {
		for (int i = 0; i < count; ++i) {
			Tri[i] = tri[i];
		}
		return;
	}

	//determine largest box dimension: x, y, or z
	int largestDim = 0; //default to x dimension;
	float largestMag = BoxMax.x - BoxMin.x;

	//check y and z with x;
	for (int i = 0; i < 2; ++i) {
		float currentMag = BoxMax[i] - BoxMin[i];
		if (largestMag < currentMag) {
			largestMag = currentMag;
			largestDim = i;
		}
	}


	//compute splitting plane halfway along largest dimension:
	Vector3 planeNormal, planePosition;

	//get center of box for center of plane:
	for (int i = 0; i < 3; ++i) {
		planePosition[i] = (BoxMax[i] - BoxMin[i]) / 2;
	}

	//find normal:
	switch (largestDim) {
		//X is the largest dimension:
		case 0:
		{
				  planeNormal = Vector3(0.0f, 1.0f, 1.0f);
				  planeNormal.Normalize();
		}
		//Y is the largest dimension:
		case 1:
		{
				  planeNormal = Vector3(1.0f, 0.0f, 1.0f);
				  planeNormal.Normalize();
		}
			//Z is the largest dimension:
		case 2:
		{
				  planeNormal = Vector3(1.0f, 1.0f, 0.0f);
				  planeNormal.Normalize();
		}
	}
	
	//Allocate two new temporary arrays
	Triangle **tri1 = new Triangle*[count];
	Triangle **tri2 = new Triangle*[count];
	int count1 = 0, count2 = 0;

	//place triangles into group 1 or group 2;
	for (int i = 0; i < count; ++i) {

		//check where the center lies
		if (tri[i]->ComputeCenter()[largestDim] < planePosition[largestDim]) {
			//less, so place in group 1
			tri1[count1] = tri[i];
			++count1;
		}
		else {
			//greater or equal so place in group 2
			tri2[count2] = tri[i];
			++count2;
		}
	}

	//check if either group is empty, if so move (at least) 1 triangle into that group
	if (count1 == 0) {
		tri1[0] = tri2[count2 - 1];
		//compensate the counts:
		++count1;
		--count2;
	}
	else if (count2 == 0) {
		tri2[0] = tri1[count1 - 1];
		//compensate the counts:
		++count2;
		--count1;
	}

	//recursively build sub-trees
	Child1 = new BoxTreeNode;
	Child2 = new BoxTreeNode;
	Child1->Contruct(count1, tri1);
	Child2->Contruct(count2, tri2);

	//free up arrays
	delete []tri1;
	delete []tri2;
}