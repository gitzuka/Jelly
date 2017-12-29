#include "Physics.h"
#include "Spring.h"

Physics::Physics() : m_deltaTime(0.01f), m_c1(1.0f), m_k(1.0f)
{
}

Physics::~Physics()
{
}

QVector3D Physics::calculateSpringsForce(const Spring &spring) const
{
	float l = spring.getInitialLength() - spring.getCurrLength();
	QVector3D direction = getDirectionVec(spring.getPoint(true).getPosition(), spring.getPoint(false).getPosition()).normalized();
	//return QVector3D(-spring.getElasticity() * l * direction);
	return QVector3D(-m_c1 * l * direction);
}

QVector3D Physics::calculatePointsForce(const JellyPoint &point) const
{
	return QVector3D(-m_k * point.getVelocity());
}

void Physics::update(const std::vector<Spring>& springs, std::vector<JellyPoint>& points)
{
	for (std::vector<Spring>::const_iterator springIt = springs.begin(); springIt != springs.end(); ++springIt)
	{
		
	}
}

void Physics::setFriction(double friction)
{
	m_k = friction;
}

void Physics::setElasticity(double elasticity)
{
	m_c1 = elasticity;
}

QVector3D Physics::calculateVelocity(const JellyPoint &point) const
{
	//return QVector3D(m_deltaTime * point.getVelocity() / point.getMass());
	return QVector3D(m_deltaTime * point.getForce() / point.getMass());
	//m_veloctiy = (m_nextPosition - m_prevPosition) / (2.0f * m_deltaTime);
}

//void Physics::updateAcceleration() const
//{
//	//m_acceleration = (m_nextPosition - 2.0f * m_position + m_prevPosition) / (m_deltaTime * m_deltaTime);
//}

QVector3D Physics::calculatePosition(const JellyPoint &point) const
{
	return QVector3D(point.getVelocity() * m_deltaTime);
	/*m_nextPosition = m_deltaTime * m_deltaTime * (m_f + m_g + m_h) / m_mass + 2.0f * m_position - m_prevPosition;
	updateVelocity();
	updateAcceleration();
	m_prevPosition = m_position;
	m_position = m_nextPosition;*/
}

QVector3D Physics::getDirectionVec(const QVector3D& p1, const QVector3D& p2) const
{
	return QVector3D(p2 - p1);
}
