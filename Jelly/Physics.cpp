#include "Physics.h"
#include "Spring.h"

Physics::Physics() : m_k(1.0f), m_c1(1.0f), m_c2(1.0f), m_deltaTime(0.01f), m_mass(1)
{
}

Physics::~Physics()
{
}

QVector3D Physics::calculateSpringsForce(const Spring &spring, float c) const
{
	float l = spring.getInitialLength() - spring.getCurrLength();
	QVector3D direction = getDirectionVec(spring.getPoint(true).getPosition(), spring.getPoint(false).getPosition()).normalized();
	return QVector3D(-c * l * direction);
}

QVector3D Physics::calculatePointsForce(const JellyPoint &point) const
{
	return QVector3D(-m_k * point.getVelocity());
}

void Physics::setMass(double mass)
{
	m_mass = mass;
}

void Physics::setFriction(double friction)
{
	m_k = friction;
}

void Physics::setElasticityC1(double elasticity)
{
	m_c1 = elasticity;
}

void Physics::setElasticityC2(double elasticity)
{
	m_c2 = elasticity;
}

QVector3D Physics::calculateVelocity(const JellyPoint &point) const
{
	//return QVector3D(m_deltaTime * point.getForce() / point.getMass());
	return QVector3D(m_deltaTime * point.getForce() / m_mass);
}

float Physics::getC1() const
{
	return m_c1;
}

float Physics::getC2() const
{
	return m_c2;
}

QVector3D Physics::calculatePosition(const JellyPoint &point) const
{
	return QVector3D(point.getVelocity() * m_deltaTime);
}

QVector3D Physics::getDirectionVec(const QVector3D& p1, const QVector3D& p2) const
{
	return QVector3D(p2 - p1);
}
