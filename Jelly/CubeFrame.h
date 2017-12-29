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
	void getVerticesPositions(std::vector<QVector3D> &positions) const;

private:
	float m_edgeLength;
	QVector3D m_color;
};