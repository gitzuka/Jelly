#pragma once
#include "Mesh.h"
#include "Spring.h"

class JellyCube : public Mesh
{
public:
	JellyCube(GLenum drawMode, QVector3D color, float edgeLength);
	~JellyCube();

	void generateVertices() override;
	void generateSprings();
	void setEdgeLength(float edgeLength);
private:
	float m_edgeLength;
	QVector3D m_color;
	std::vector<Spring> m_springs;
};
