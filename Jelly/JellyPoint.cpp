#include "JellyPoint.h"

JellyPoint::JellyPoint(const QVector3D &position, float mass, QVector3D velocity)
	: m_position(position), m_mass(mass), m_velocity(velocity), m_force(QVector3D(0, 0, 0))
{
}

JellyPoint::JellyPoint(const QVector3D &position) :
	m_position(position), m_mass(1), m_velocity(QVector3D(0,0,0)), m_force(QVector3D(0,0,0))
{
}

JellyPoint::~JellyPoint()
{
}

void JellyPoint::updatePosition(const QVector3D &position)
{
	m_position += position;
}

void JellyPoint::setPosition(const QVector3D& position)
{
	m_position = position;
}

void JellyPoint::setMass(float mass)
{
	m_mass = mass;
}

void JellyPoint::setVelocity(QVector3D velocity)
{
	m_velocity = velocity;
}

void JellyPoint::addForce(const QVector3D &force)
{
	m_force += force;
}

void JellyPoint::addVeloctiy(const QVector3D &velocity)
{
	m_velocity += velocity;
}

void JellyPoint::resetForce()
{
	m_force = QVector3D(0, 0, 0);
}

const QVector3D &JellyPoint::getPosition() const
{
	return m_position;
}

float JellyPoint::getMass() const
{
	return m_mass;
}

const QVector3D& JellyPoint::getVelocity() const
{
	return m_velocity;
}

const QVector3D& JellyPoint::getForce() const
{
	return m_force;
}
