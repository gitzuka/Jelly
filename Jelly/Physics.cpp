#include "Physics.h"
#include "Spring.h"

Physics::Physics() : m_k(0.1f), m_c1(1.0f), m_c2(5.0f), m_deltaTime(0.01f), m_mass(0.1f), m_bounceElasticity(0), m_maxStep(1000)
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

void Physics::setBoundingX(const QVector2D boundingX)
{
	m_boundingX = boundingX;
}

void Physics::setBoundingY(const QVector2D boundingY)
{
	m_boundingY = boundingY;
}

void Physics::setBoundingZ(const QVector2D boundingZ)
{
	m_boundingZ = boundingZ;
}

void Physics::setBounceFactor(double bounceFactor)
{
	m_bounceElasticity = bounceFactor;
}

QVector3D Physics::calculateVelocity(const JellyPoint &point) const
{
	//return QVector3D(m_deltaTime * point.getForce() / point.getMass());
	return QVector3D(m_deltaTime * point.getForce() / m_mass);
}

QVector3D Physics::calculateBounces(JellyPoint &point) const
{
	float delta = 0.000000001f;
	//QVector3D pos;
	QVector3D pos;// = calculateElasticBounce(point);
	m_bounceElasticity < delta ? pos = calculateNonElasticBounce(point) : pos = calculateElasticBounce(point);
	return pos;
	/*float delta = 0.000000001f;
	QVector3D velocity = point.getVelocity();
	if (point.getPosition().x() > m_boundingX.y())
	{
		QVector3D pos = point.getPosition();
		pos.setX(m_boundingX.y() - delta);
		point.setPosition(pos);
		velocity.setX(-velocity.x() * m_bounceElasticity);
	}
	return velocity;*/
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

//QVector3D Physics::calculateBounceX(JellyPoint& point) const
//{
//	float delta = 0.000000001f;
//	QVector3D velocity = point.getVelocity();
//	QVector3D pos = point.getPosition();
//	if (point.getPosition().x() > m_boundingX.y())
//	{
//		pos.setX(m_boundingX.y() - delta);
//		velocity.setX(-velocity.x() * m_bounceElasticity);
//	}
//	else if (point.getPosition().x() < m_boundingX.x())
//	{
//		pos.setX(m_boundingX.x() + delta);
//		velocity.setX(-velocity.x() * m_bounceElasticity);
//	}
//
//	if (point.getPosition().y() > m_boundingY.y())
//	{
//		pos.setY(m_boundingY.y() - delta);
//		velocity.setY(-velocity.y() * m_bounceElasticity);
//	}
//	else if (point.getPosition().y() < m_boundingY.x())
//	{
//		pos.setY(m_boundingY.x() + delta);
//		velocity.setY(-velocity.y() * m_bounceElasticity);
//	}
//
//	if (point.getPosition().z() > m_boundingZ.y())
//	{
//		pos.setZ(m_boundingZ.y() - delta);
//		velocity.setZ(-velocity.z() * m_bounceElasticity);
//	}
//	else if (point.getPosition().z() < m_boundingZ.x())
//	{
//		pos.setZ(m_boundingZ.x() + delta);
//		velocity.setZ(-velocity.z() * m_bounceElasticity);
//	}
//	point.setPosition(pos);
//	return velocity;
//}

QVector3D Physics::calculateElasticBounce(JellyPoint& point) const
{
	QVector3D velocity;// = point.getVelocity();
	QVector3D pos;// = point.getPosition();
	int i = 0;
	while ((point.getPosition().x() + calculatePosition(point).x() >= m_boundingX.y() || point.getPosition().x() + calculatePosition(point).x() <= m_boundingX.x()) && i < m_maxStep)
		//if (point.getPosition().x() + calculatePosition(point).x() >= m_boundingX.y() || point.getPosition().x() + calculatePosition(point).x() <= m_boundingX.x())
	{
		pos = calculatePosition(point);
		pos.setX(-pos.x());
		velocity = point.getVelocity();
		velocity.setX(-velocity.x() * m_bounceElasticity);
		point.setVelocity(velocity);
		++i;
	}
	i = 0;
	while ((point.getPosition().y() + calculatePosition(point).y() >= m_boundingX.y() || point.getPosition().y() + calculatePosition(point).y() <= m_boundingX.x()) && i < m_maxStep)
		//if (point.getPosition().y() + calculatePosition(point).y() >= m_boundingX.y() || point.getPosition().y() + calculatePosition(point).y() <= m_boundingX.x())
	{
		pos = calculatePosition(point);
		pos.setY(-pos.y());
		velocity = point.getVelocity();
		velocity.setY(-velocity.y() * m_bounceElasticity);
		point.setVelocity(velocity);
		++i;
	}
	i = 0;

	while ((point.getPosition().z() + calculatePosition(point).z() >= m_boundingX.y() || point.getPosition().z() + calculatePosition(point).z() <= m_boundingX.x()) && i < m_maxStep)
		//	if (point.getPosition().z() + calculatePosition(point).z() >= m_boundingX.y() || point.getPosition().z() + calculatePosition(point).z() <= m_boundingX.x())
	{
		pos = calculatePosition(point);
		pos.setZ(-pos.z());
		velocity = point.getVelocity();
		velocity.setZ(-velocity.z() * m_bounceElasticity);
		point.setVelocity(velocity);
		++i;
	}
	return velocity;
}

QVector3D Physics::calculateNonElasticBounce(JellyPoint& point) const
{
	float delta = 0.0001f;
	QVector3D velocity = point.getVelocity();
	QVector3D pos = point.getPosition();
	int i = 0;
	while (point.getPosition().x() > m_boundingX.y() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos = point.getPosition();pos.setX(m_boundingX.y() - delta);
		point.setPosition(pos);
		velocity.setX(-velocity.x() * m_bounceElasticity);
		++i;
	}
	i = 0;
	while (point.getPosition().x() < m_boundingX.x() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos.setX(m_boundingX.x() + delta);
		point.setPosition(pos);
		velocity.setX(-velocity.x() * m_bounceElasticity);
		++i;
	}
	i = 0;

	while (point.getPosition().y() > m_boundingY.y() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos.setY(m_boundingY.y() - delta);
		point.setPosition(pos);
		velocity.setY(-velocity.y() * m_bounceElasticity);
		++i;
	}
	i = 0;
	while (point.getPosition().y() < m_boundingY.x() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos.setY(m_boundingY.x() + delta);
		point.setPosition(pos);
		velocity.setY(-velocity.y() * m_bounceElasticity);
		++i;
	}
	i = 0;

	while (point.getPosition().z() > m_boundingZ.y() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos.setZ(m_boundingZ.y() - delta);
		point.setPosition(pos);
		velocity.setZ(-velocity.z() * m_bounceElasticity);
		++i;
	}
	i = 0;
	while (point.getPosition().z() < m_boundingZ.x() && i<m_maxStep)
	{
		pos = point.getPosition();
		pos.setZ(m_boundingZ.x() + delta);
		point.setPosition(pos);
		velocity.setZ(-velocity.z() * m_bounceElasticity);
		++i;
	}
	/*if (point.getPosition().x() >= m_boundingX.y())
	{
		pos.setX(m_boundingX.y() - delta);
		velocity.setX(-velocity.x() * m_bounceElasticity);
	}
	else if (point.getPosition().x() <= m_boundingX.x())
	{
		pos.setX(m_boundingX.x() + delta);
		velocity.setX(-velocity.x() * m_bounceElasticity);
	}

	if (point.getPosition().y() >= m_boundingY.y())
	{
		pos.setY(m_boundingY.y() - delta);
		velocity.setY(-velocity.y() * m_bounceElasticity);
	}
	else if (point.getPosition().y() <= m_boundingY.x())
	{
		pos.setY(m_boundingY.x() + delta);
		velocity.setY(-velocity.y() * m_bounceElasticity);
	}

	if (point.getPosition().z() >=m_boundingZ.y())
	{
		pos.setZ(m_boundingZ.y() - delta);
		velocity.setZ(-velocity.z() * m_bounceElasticity);
	}
	else if (point.getPosition().z() <= m_boundingZ.x())
	{
		pos.setZ(m_boundingZ.x() + delta);
		velocity.setZ(-velocity.z() * m_bounceElasticity);
	}*/
	return velocity;
}

QVector3D Physics::getDirectionVec(const QVector3D& p1, const QVector3D& p2) const
{
	return QVector3D(p2 - p1);
}
