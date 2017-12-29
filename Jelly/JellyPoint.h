#pragma once
#include <Qvector3D>

class JellyPoint
{
public:
	JellyPoint(const QVector3D &position, float mass, QVector3D velocity);
	JellyPoint(const QVector3D &position);
	~JellyPoint();

	void updatePosition(const QVector3D &position);
	void setMass(float mass);
	void setVelocity(QVector3D velocity);
	void addForce(const QVector3D &force);
	void addVeloctiy(const QVector3D &velocity);
	void resetForce();
	const QVector3D& getPosition() const;
	float getMass() const;
	const QVector3D& getVelocity() const;
	const QVector3D& getForce() const;

private:
	QVector3D m_position;
	float m_mass;
	QVector3D m_velocity;
	QVector3D m_force;
};
