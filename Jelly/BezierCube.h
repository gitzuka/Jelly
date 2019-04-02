#pragma once
#include "Mesh.h"

class BezierCube : public Mesh
{
public:
	BezierCube(GLenum drawMode, int index, int divisions, QVector3D color, bool model);
	BezierCube(const QVector<Vertex>& vertices, const QVector<GLushort>& indices, GLenum drawMode, int index, QVector3D color, bool model);
	~BezierCube();

	void generateVertices() override;
	void generateIndices() override;
	bool isModel() const;
	//const QVector<QVector3D>& getPositions() const;

private:
	int m_divisions;
	QVector3D m_color;
	const bool m_model;
	//QVector<QVector3D> m_positions;

	//void fillPositions();
};
