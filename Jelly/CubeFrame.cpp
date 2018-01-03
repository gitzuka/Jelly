#include "CubeFrame.h"
#include "Camera.h"

CubeFrame::CubeFrame(GLenum drawMode, int index, QVector3D color = QVector3D(1.0f, 0, 0), float edgeLength = 0.1f)
	: Mesh(drawMode, index), m_edgeLength(edgeLength), m_color(color), m_pitch(0), m_yaw(0)
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

void CubeFrame::getVerticesPositions(std::vector<QVector3D>& positions) const
{
	positions.reserve(8);
	for (QVector<Vertex>::const_iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		//QVector3D pos = it->getPosition();
		//pos.setX(pos.x() + m_modelMatrix.row(0).w());
		//pos.setY(pos.y() + m_modelMatrix.row(1).w());
		//pos.setZ(pos.z() + m_modelMatrix.row(2).w());
		////positions.push_back(pos);*/
		//QVector3D test = QVector3D(Camera::transform(QVector4D(it->getPosition(), 1), getModelMatrix()));
		positions.push_back(QVector3D(Camera::transform(QVector4D(it->getPosition(), 1), getModelMatrix())));
	}
}

void CubeFrame::setPitch(float pitch)
{
	m_pitch = clipAngle(m_pitch + pitch);
}

void CubeFrame::setYaw(float yaw)
{
	m_yaw = clipAngle(m_yaw + yaw);
}

void CubeFrame::moveFrame(const QMatrix4x4& mat)
{
	setModelMatrix(mat);
	rotate(m_pitch, m_yaw);
}

void CubeFrame::rotate(float pitch, float yaw)
{
	setPitch(pitch);
	setYaw(yaw);
	//camera inv?
	QMatrix4x4 mat = Camera::createTranslation(QVector3D(getModelMatrix().column(3)));
	mat.rotate(m_pitch, QVector3D(1, 0, 0));
	mat.rotate(m_yaw, QVector3D(0, 1, 0));
	setModelMatrix(mat);
}

float CubeFrame::clipAngle(float angle) const
{
	int ang = angle;
	float a = angle >= 0 ? 0 : 360;
	a += ang % 360;
	return a;
}
