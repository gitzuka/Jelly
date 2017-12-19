#include "Mesh.h"

Mesh::Mesh(GLenum drawMode) : m_drawMode(drawMode)
{
}

Mesh::Mesh(const std::vector<Vertex>& vertices, GLenum drawMode) : m_vertices(vertices), m_drawMode(drawMode)
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

const std::vector<Vertex>& Mesh::getVertices() const
{
	return m_vertices;
}

//const QVector<int>& Mesh::getIndices() const
//{
//	return m_indices;
//}

//const QVector<Vertex>& Mesh::getNormals() const
//{
//	return m_normals;
//}
