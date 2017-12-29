#include "Spring.h"
#include "Vertex.h"

//Spring::Spring(const QVector3D &p1, const QVector3D &p2) : m_initialLength(p1.distanceToPoint(p2)), m_p1(p1), m_p2(p2)
//{
//}

Spring::Spring(JellyPoint& p1, JellyPoint& p2) : m_p1(p1), m_p2(p2), m_initialLength(p1.getPosition().distanceToPoint(p2.getPosition()))
{
}

Spring::~Spring()
{
}

float Spring::getInitialLength() const
{
	return m_initialLength;
}

float Spring::getCurrLength() const
{
	return abs((m_p1.getPosition() - m_p2.getPosition()).length());
}

//float Spring::getElasticity() const
//{
//	return m_elasticity;
//}

const JellyPoint &Spring::getPoint(bool first) const
{
	return (first ? m_p1 : m_p2);
}

void Spring::applyForce(const QVector3D &force)
{
	m_p1.addForce(force);
	m_p2.addForce(-force);
}

void Spring::setInitialLength(float length)
{
	m_initialLength = length;
}

//void Spring::setElasticity(float elasticity)
//{
//	m_elasticity = elasticity;
//}

//void Spring::setCurrLength(float length)
//{
//	m_currLength = length;
//}

void Spring::setInitialLength(const QVector3D &p1, const QVector3D &p2)
{
	setInitialLength(p1.distanceToPoint(p2));
}

//void Spring::setCurrLength(const QVector3D &p1, const QVector3D &p2)
//{
//	setCurrLength(p1.distanceToPoint(p2));
//}
