#pragma once
#include "Mesh.h"

class Point3D : public Mesh
{
public:
	Point3D(GLenum drawMode, int index);
	~Point3D();

	void generateVertices() override;
	void generateIndices() override;

private:
	float m_edgeLength;
};
