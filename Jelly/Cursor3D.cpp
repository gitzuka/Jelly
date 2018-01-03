#include "Cursor3D.h"
#include "Camera.h"

Cursor3D::Cursor3D(GLenum drawMode, int index)
	: Mesh(drawMode, index), m_position(QVector3D(0,0,0)), m_length(0.2), m_mousePosX(0), m_mousePosY(0)
{
	Cursor3D::generateVertices();
	Cursor3D::generateIndices();
}

Cursor3D::~Cursor3D()
{
}

void Cursor3D::generateVertices()
{
	m_vertices.reserve(6);
	m_vertices.push_back(Vertex(QVector3D(0, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	m_vertices.push_back(Vertex(QVector3D(0, m_length, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	m_vertices.push_back(Vertex(QVector3D(0, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	m_vertices.push_back(Vertex(QVector3D(m_length, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	m_vertices.push_back(Vertex(QVector3D(0, 0, 0), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
	m_vertices.push_back(Vertex(QVector3D(0, 0, -m_length), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
}

void Cursor3D::generateIndices()
{
	m_indices.reserve(m_vertices.count());
	for (int i = 0; i < m_vertices.count(); ++i)
	{
		m_indices.push_back(i);
	}
}

QVector3D Cursor3D::setPosition(float mouseX, float mouseY, bool z, float width, float heigth, const Camera &cam)
{
	float x = mouseX - width / 2.0f;
	float y = mouseY - heigth / 2.0f;
	float cursorPosX = (x - m_mousePosX) / width;
	float cursorPosY = 0, cursorPosZ = 0;
	if (z)
	{
		cursorPosZ = (y - m_mousePosY) / heigth;
	}
	else
	{
		cursorPosY = -(y - m_mousePosY) / heigth;
	}
	m_position.setX(cursorPosX + m_position.x());
	m_position.setY(cursorPosY + m_position.y());
	m_position.setZ(cursorPosZ + m_position.z());
	QVector3D trans = QVector3D(- cam.m_viewMatrix.row(0).w() + m_position.x(),
		- cam.m_viewMatrix.row(1).w() + m_position.y(),
		- cam.m_viewMatrix.row(2).w() - 3 + m_position.z());
	setModelMatrix((Camera::createRotationX(cam.m_pitch) * Camera::createRotationY(cam.m_yaw)).inverted()
		* Camera::createTranslation(trans));

	m_mousePosX = x;
	m_mousePosY = y;
	return m_position;
	/*float x = mouseX - width / 2.0f;
	float y = mouseY - heigth / 2.0f;
	float cursorPosX = (x - m_mousePosX) / width;
	float cursorPosY = 0, cursorPosZ = 0;
	if (z)
	{
		cursorPosZ = (y - m_mousePosY) / heigth;
	}
	else
	{
		cursorPosY = - (y - m_mousePosY) / heigth;
	}
	QVector3D trans = QVector3D(cursorPosX - cam.m_viewMatrix.row(0).w() + m_position.x(),
		cursorPosY - cam.m_viewMatrix.row(1).w() + m_position.y(),
		cursorPosZ - cam.m_viewMatrix.row(2).w() - 3 + m_position.z());
	setModelMatrix((Camera::createRotationX(cam.m_pitch) * Camera::createRotationY(cam.m_yaw)).inverted()
		* Camera::createTranslation(trans));
	m_position.setX(cursorPosX + m_position.x());
	m_position.setY(cursorPosY + m_position.y());
	m_position.setZ(cursorPosZ + m_position.z());

	m_mousePosX = x;
	m_mousePosY = y;*/
}

void Cursor3D::rotate(float pitch, float yaw)
{
	//QVector3D tran = QVector3D(getModelMatrix().row(0).w(), getModelMatrix().row(2).w(), getModelMatrix().row(1).w());
	//setModelMatrix(Camera::createTranslation(-tran) * Camera::createRotationY(yaw) * Camera::createTranslation(tran));
}

QVector3D Cursor3D::getPosition() const
{
	QVector3D pos = QVector3D(m_modelMatrix.column(3));
	return pos;
}
