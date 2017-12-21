#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(GLenum drawMode) : m_drawMode(drawMode)
{
}

Mesh::Mesh(const QVector<Vertex>& vertices, GLenum drawMode) : m_vertices(vertices), m_drawMode(drawMode)
{
}

//Mesh::Mesh(const QVector<Vertex>& vertices, const QVector<int>& indices, const QVector<Vertex>& normals)
//	: m_vertices(vertices), m_indices(indices), m_normals(normals)
//{
//}

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

//const QVector<int>& Mesh::getIndices() const
//{
//	return m_indices;
//}

//const QVector<Vertex>& Mesh::getNormals() const
//{
//	return m_normals;
//}
