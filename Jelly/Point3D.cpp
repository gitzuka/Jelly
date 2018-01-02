#include "Point3D.h"

Point3D::Point3D(GLenum drawMode, int index)
	: Mesh(drawMode, index), m_edgeLength(0.008f)
{
	Point3D::generateVertices();
	Point3D::generateIndices();
}

Point3D::~Point3D()
{
}

void Point3D::generateVertices()
{
	QVector3D pointNormal = QVector3D(0, 0, 0);
	QVector3D m_color = QVector3D(1, 1, 0);
	QVector<QVector3D> cubePos = {
		QVector3D(-m_edgeLength / 2.0f, m_edgeLength / 2.0f, -m_edgeLength / 2.0f) , //left top //front 0
		QVector3D(m_edgeLength / 2.0f, m_edgeLength / 2.0f, -m_edgeLength / 2.0f), //right top 1
		QVector3D(m_edgeLength / 2.0f, -m_edgeLength / 2.0f, -m_edgeLength / 2.0f) , //right bottom 2 
		QVector3D(-m_edgeLength / 2.0f, -m_edgeLength / 2.0f, -m_edgeLength / 2.0f)  , //left bottom 3

		QVector3D(-m_edgeLength / 2.0f, m_edgeLength / 2.0f, m_edgeLength / 2.0f)  , //back 4
		QVector3D(m_edgeLength / 2.0f, m_edgeLength / 2.0f, m_edgeLength / 2.0f)  , //5
		QVector3D(m_edgeLength / 2.0f, -m_edgeLength / 2.0f, m_edgeLength / 2.0f)  , //6 
		QVector3D(-m_edgeLength / 2.0f, -m_edgeLength / 2.0f, m_edgeLength / 2.0f) }; //7

	m_vertices.reserve(8);
	m_vertices = {
		Vertex(cubePos.at(0), m_color, pointNormal), //right
		Vertex(cubePos.at(1), m_color, pointNormal),
		Vertex(cubePos.at(2), m_color, pointNormal),
		Vertex(cubePos.at(3), m_color, pointNormal),
									   
		Vertex(cubePos.at(4), m_color, pointNormal), //left
		Vertex(cubePos.at(5), m_color, pointNormal),
		Vertex(cubePos.at(6), m_color, pointNormal),
		Vertex(cubePos.at(7), m_color, pointNormal)
	};
}

void Point3D::generateIndices()
{
	m_indices.reserve(24);

	m_indices.append(0);
	m_indices.append(1);
	m_indices.append(1);
	m_indices.append(2);
	m_indices.append(2);
	m_indices.append(3);
	m_indices.append(3);
	m_indices.append(0);

	m_indices.append(4);
	m_indices.append(5);
	m_indices.append(5);
	m_indices.append(6);
	m_indices.append(6);
	m_indices.append(7);
	m_indices.append(7);
	m_indices.append(4);

	m_indices.append(0);
	m_indices.append(4);
	m_indices.append(2);
	m_indices.append(6);

	m_indices.append(1);
	m_indices.append(5);
	m_indices.append(3);
	m_indices.append(7);
}
