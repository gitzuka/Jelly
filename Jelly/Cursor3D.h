#pragma once
#include "Mesh.h"

class Camera;

class Cursor3D : public Mesh
{
public:
	Cursor3D(GLenum drawMode, int index);
	~Cursor3D();

	void generateVertices() override;
	void generateIndices() override;
	QVector3D setPosition(float mouseX, float mouseY, bool z, float width, float heigth, const Camera &viewMat);
	void rotate(float pitch, float yaw);
	QVector3D getPosition() const;
	float m_mousePosX;
	float m_mousePosY;

private:
	QVector3D m_position;
	float m_length;
};
