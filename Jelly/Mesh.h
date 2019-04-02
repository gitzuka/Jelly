#pragma once
#include "Vertex.h"
#include <qvector.h>
#include <qopengl.h>
#include <QMatrix4x4>

class Mesh
{
public:
	Mesh(const QVector<Vertex>& vertices, const QVector<GLushort>& indices, GLenum drawMode, int index);
	Mesh(GLenum drawMode, int index);
	virtual ~Mesh() = 0;

	virtual void generateVertices() = 0;
	virtual void generateIndices() = 0;

	GLenum getDrawMode() const;
	const QVector<Vertex>& getVertices() const;
	const QVector<GLushort>& getIndices() const;
	const QMatrix4x4& getModelMatrix() const;
	void setModelMatrix(const QMatrix4x4 &mat);
	int getIndex() const;
	void setNormals(const QVector<QVector3D> &normals);

protected:
	QVector<Vertex> m_vertices;
	QVector<GLushort> m_indices;
	QMatrix4x4 m_modelMatrix;
	GLenum m_drawMode;

private:
	const int m_index;
};
