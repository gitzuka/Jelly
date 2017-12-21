#include "Spring.h"
#include "Vertex.h"

Spring::Spring(const QVector3D &p1, const QVector3D &p2) : m_initialLength(p1.distanceToPoint(p2)), m_currLength(m_initialLength), m_p1(p1), m_p2(p2)
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
	return m_currLength;
}

const JellyPoint &Spring::getPoint(bool first) const
{
	return (first ? m_p1 : m_p2);
}

void Spring::setInitialLength(float length)
{
	m_initialLength = length;
}

void Spring::setCurrLength(float length)
{
	m_currLength = length;
}

void Spring::setInitialLength(const QVector3D &p1, const QVector3D &p2)
{
	setInitialLength(p1.distanceToPoint(p2));
}

void Spring::setCurrLength(const QVector3D &p1, const QVector3D &p2)
{
	setCurrLength(p1.distanceToPoint(p2));
}
