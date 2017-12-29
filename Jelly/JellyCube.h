#pragma once
#include "Mesh.h"
#include "Spring.h"

class JellyCube : public Mesh
{
public:
	JellyCube(GLenum drawMode, int index, QVector3D color, float edgeLength);
	~JellyCube();

	void generateVertices() override;
	void generateIndices() override;
	void generateSprings(std::vector<Spring> &springs, std::vector<JellyPoint> &jellyPoints);
	void generateFrameSprings(std::vector<Spring> &springs, std::vector<JellyPoint> &jellyPoints);
	void generateJellyPoints(std::vector<JellyPoint> &jellyPoints);
	void setEdgeLength(float edgeLength);
	void updateVerticesPositions(const std::vector<JellyPoint> &positions);

private:
	float m_edgeLength;
	QVector3D m_color;
	//std::vector<Spring> m_springs;
};
