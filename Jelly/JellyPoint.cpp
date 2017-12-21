#include "JellyPoint.h"

JellyPoint::JellyPoint(const QVector3D &position, float mass, float velocity) 
	: m_position(position), m_mass(mass), m_velocity(velocity)
{
}

JellyPoint::JellyPoint(const QVector3D &position) : m_position(position)
{
}

JellyPoint::~JellyPoint()
{
}

void JellyPoint::setPosition(const QVector3D &position)
{
	m_position = position;
}

void JellyPoint::setMass(float mass)
{
	m_mass = mass;
}

void JellyPoint::setVelocity(float velocity)
{
	m_velocity = velocity;
}

const QVector3D & JellyPoint::getPosition() const
{
	return m_position;
}

float JellyPoint::getMass() const
{
	return m_mass;
}

float JellyPoint::getVelocity() const
{
	return m_velocity;
}
