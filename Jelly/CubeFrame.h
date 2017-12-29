#pragma once
#include "Mesh.h"

class CubeFrame : public Mesh
{
public:
	CubeFrame(GLenum drawMode, int index, QVector3D color, float edgeLength);
	~CubeFrame();

	void generateVertices() override;
	void generateIndices() override;
	void setEdgeLength(float edgeLength);

private:
	float m_edgeLength;
	QVector3D m_color;
};