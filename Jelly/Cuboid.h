#pragma once
#include "Mesh.h"
#include <qvector2d.h>

class Cuboid : public Mesh
{
public:
	Cuboid(GLenum drawMode, int index, float edgeLength);
	~Cuboid();

	void generateVertices() override;
	void generateIndices() override;
	const QVector2D& getBoundingX() const;
	const QVector2D& getBoundingY() const;
	const QVector2D& getBoundingZ() const;

private:
	float m_edgeLength;
	QVector2D m_boundingX;
	QVector2D m_boundingY;
	QVector2D m_boundingZ;

	void setBoundings();
};
