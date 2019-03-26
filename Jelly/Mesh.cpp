#include "Mesh.h"

Mesh::Mesh(GLenum drawMode, int index) : m_drawMode(drawMode), m_index(index)
{
}

Mesh::Mesh(const QVector<Vertex>& vertices, const QVector<GLushort>& indices, GLenum drawMode, int index)
	: m_vertices(vertices), m_indices(indices), m_drawMode(drawMode), m_index(index)
{
}

Mesh::~Mesh()
{
}

GLenum Mesh::getDrawMode() const
{
	return m_drawMode;
}

const QVector<Vertex>& Mesh::getVertices() const
{
	return m_vertices;
}

const QVector<GLushort>& Mesh::getIndices() const
{
	return m_indices;
}

const QMatrix4x4& Mesh::getModelMatrix() const
{
	return m_modelMatrix;
}

void Mesh::setModelMatrix(const QMatrix4x4& mat)
{
	m_modelMatrix = mat;
}

int Mesh::getIndex() const
{
	return m_index;
}
