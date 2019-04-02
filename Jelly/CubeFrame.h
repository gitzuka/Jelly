#pragma once
#include "Mesh.h"

class Camera;

class CubeFrame : public Mesh
{
public:
	CubeFrame(GLenum drawMode, int index, QVector3D color, float edgeLength);
	~CubeFrame();

	void generateVertices() override;
	void generateIndices() override;
	void setEdgeLength(float edgeLength);
	void getVerticesPositions(std::vector<QVector3D> &positions) const;
	void setPitch(float pitch);
	void setYaw(float yaw);
	QMatrix4x4 getRotationmat() const;
	void moveFrame(const QMatrix4x4 &mat, const Camera &cam);
	void rotate(float pitch, float yaw, const Camera &cam);

private:
	float m_edgeLength;
	float m_pitch;
	float m_yaw;
	QVector3D m_color;

	float clipAngle(float angle) const;
};
