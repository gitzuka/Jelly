#include "Cuboid.h"

Cuboid::Cuboid(GLenum drawMode, int index, float edgeLength)
	: Mesh(drawMode, index), m_edgeLength(edgeLength)
{
	Cuboid::generateVertices();
	Cuboid::generateIndices();
	setBoundings();
}

Cuboid::~Cuboid()
{
}

void Cuboid::generateVertices()
{
	QVector3D color = QVector3D(0, 1, 0);
	QVector<QVector3D> cubeNormals = {
		QVector3D(0.0f, 0.0f, 1.0f), // front face 0
		QVector3D(1.0f, 0.0f, 0.0f), //right face 1
		QVector3D(-1.0f, 0.0f, 0.0f), //left face 2
		QVector3D(0.0f, 1.0f, 0.0f), //top face 3
		QVector3D(0.0f, -1.0f, 0.0f), //bottom face 4
		QVector3D(0.0f, 0.0f, -1.0f) }; //back face 5

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
		Vertex(cubePos.at(0), color, cubeNormals.at(1)), //right
		Vertex(cubePos.at(1), color, cubeNormals.at(1)),
		Vertex(cubePos.at(2), color, cubeNormals.at(1)),
		Vertex(cubePos.at(3), color, cubeNormals.at(1)),

		Vertex(cubePos.at(4), color, cubeNormals.at(2)), //left
		Vertex(cubePos.at(5), color, cubeNormals.at(2)),
		Vertex(cubePos.at(6), color, cubeNormals.at(2)),
		Vertex(cubePos.at(7), color, cubeNormals.at(2))
	};
}

void Cuboid::generateIndices()
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

const QVector2D & Cuboid::getBoundingX() const
{
	return m_boundingX;
}

const QVector2D & Cuboid::getBoundingY() const
{
	return m_boundingY;
}

const QVector2D & Cuboid::getBoundingZ() const
{
	return m_boundingZ;
}

void Cuboid::setBoundings()
{
	m_boundingX = QVector2D(-m_edgeLength / 2.0f, m_edgeLength / 2.0f);
	m_boundingY = QVector2D(-m_edgeLength / 2.0f, m_edgeLength / 2.0f);
	m_boundingZ = QVector2D(-m_edgeLength / 2.0f, m_edgeLength / 2.0f);
}
