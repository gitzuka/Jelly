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
	void setPosition(float mouseX, float mouseY, bool z, float width, float heigth, const Camera &viewMat);
	void rotate(float pitch, float yaw);
	QVector3D getPosition() const;

private:
	QVector3D m_position;
	float m_mousePosX;
	float m_mousePosY;
	float m_length;
};
