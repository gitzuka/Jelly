#include "CubeFrame.h"

CubeFrame::CubeFrame(GLenum drawMode, int index, QVector3D color = QVector3D(1.0f, 0, 0), float edgeLength = 0.1f)
	: Mesh(drawMode, index), m_edgeLength(edgeLength), m_color(color)
{
	CubeFrame::generateVertices();
	CubeFrame::generateIndices();
}

CubeFrame::~CubeFrame()
{
}

void CubeFrame::generateVertices()
{

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
		Vertex(cubePos.at(0), m_color, cubeNormals.at(1)), //right
		Vertex(cubePos.at(1), m_color, cubeNormals.at(1)),
		Vertex(cubePos.at(2), m_color, cubeNormals.at(1)),
		Vertex(cubePos.at(3), m_color, cubeNormals.at(1)),

		Vertex(cubePos.at(4), m_color, cubeNormals.at(2)), //left
		Vertex(cubePos.at(5), m_color, cubeNormals.at(2)),
		Vertex(cubePos.at(6), m_color, cubeNormals.at(2)),
		Vertex(cubePos.at(7), m_color, cubeNormals.at(2))
	};

	//m_vertices.reserve(24);
	//m_vertices = {
	//	Vertex(cubePos.at(1), m_color, cubeNormals.at(1)), //right
	//	Vertex(cubePos.at(5), m_color, cubeNormals.at(1)),
	//	Vertex(cubePos.at(6), m_color, cubeNormals.at(1)),
	//	Vertex(cubePos.at(2), m_color, cubeNormals.at(1)),

	//	Vertex(cubePos.at(4), m_color, cubeNormals.at(2)), //left
	//	Vertex(cubePos.at(0), m_color, cubeNormals.at(2)),
	//	Vertex(cubePos.at(3), m_color, cubeNormals.at(2)),
	//	Vertex(cubePos.at(7), m_color, cubeNormals.at(2)),

	//	Vertex(cubePos.at(4), m_color, cubeNormals.at(3)), //top
	//	Vertex(cubePos.at(5), m_color, cubeNormals.at(3)),
	//	Vertex(cubePos.at(1), m_color, cubeNormals.at(3)),
	//	Vertex(cubePos.at(0), m_color, cubeNormals.at(3)),

	//	Vertex(cubePos.at(3), m_color, cubeNormals.at(4)),
	//	Vertex(cubePos.at(2), m_color, cubeNormals.at(4)),
	//	Vertex(cubePos.at(6), m_color, cubeNormals.at(4)),
	//	Vertex(cubePos.at(7), m_color, cubeNormals.at(4)), //bot

	//	Vertex(cubePos.at(0), m_color, cubeNormals.at(5)), //back
	//	Vertex(cubePos.at(1), m_color, cubeNormals.at(5)),
	//	Vertex(cubePos.at(2), m_color, cubeNormals.at(5)),
	//	Vertex(cubePos.at(3), m_color, cubeNormals.at(5)),

	//	Vertex(cubePos.at(7), m_color, cubeNormals.at(0)), //front
	//	Vertex(cubePos.at(6), m_color, cubeNormals.at(0)),
	//	Vertex(cubePos.at(5), m_color, cubeNormals.at(0)),
	//	Vertex(cubePos.at(4), m_color, cubeNormals.at(0))
	//};
}

void CubeFrame::generateIndices()
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

void CubeFrame::setEdgeLength(float edgeLength)
{
	m_edgeLength = edgeLength;
}
