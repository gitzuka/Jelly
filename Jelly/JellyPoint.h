#pragma once
#include <Qvector3D>

class JellyPoint
{
public:
	JellyPoint(const QVector3D &position, float mass, float velocity);
	JellyPoint(const QVector3D &position);
	~JellyPoint();

	void setPosition(const QVector3D &position);
	void setMass(float mass);
	void setVelocity(float velocity);
	const QVector3D& getPosition() const;
	float getMass() const;
	float getVelocity() const;

private:
	QVector3D m_position;
	float m_mass;
	float m_velocity;
};
