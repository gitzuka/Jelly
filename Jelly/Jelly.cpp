#include "Jelly.h"
#include <random>

Jelly::Jelly()
	: m_velocitiesRange(1.0f), m_positionsRange(1.0f), m_physicsStep(5), m_drawStep(30),
	m_timerPhysics(new QTimer(this)), m_timerDraw(new QTimer(this)), m_simulate(false)
{
}

Jelly::~Jelly()
{
}

void Jelly::createSpringsAndPoints(std::shared_ptr<JellyCube> jellyCube, std::shared_ptr<CubeFrame> cubeFrame)
{
	std::vector<QVector3D> framePositions;
	cubeFrame->getVerticesPositions(framePositions);
	jellyCube->generateSprings(m_springs, m_jellyPoints);
	m_normalsData.framePoints.reserve(8);
	m_framePoints.reserve(8);
	float mass = 1.0f;
	for (auto it = framePositions.begin(); it != framePositions.end(); ++it)
	{
		m_framePoints.emplace_back(JellyPoint(*it, mass, QVector3D(0, 0, 0)));
		m_normalsData.framePoints.emplace_back(JellyPoint(*it * m_normalsData.factor, mass, QVector3D(0, 0, 0)));
	}
	m_frameSprings.reserve(8);
	m_frameSprings.emplace_back(Spring(m_framePoints.at(0), m_jellyPoints.at(0)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(1), m_jellyPoints.at(3)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(2), m_jellyPoints.at(15)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(3), m_jellyPoints.at(12)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(4), m_jellyPoints.at(48)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(5), m_jellyPoints.at(51)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(6), m_jellyPoints.at(63)));
	m_frameSprings.emplace_back(Spring(m_framePoints.at(7), m_jellyPoints.at(60)));

	for (const auto &jellyPoint : m_jellyPoints)
	{
		m_normalsData.jellyPoints.emplace_back(
			JellyPoint(jellyPoint.getPosition() * m_normalsData.factor, jellyPoint.getMass(), jellyPoint.getVelocity()));
	}

	m_normalsData.frameSprings.reserve(8);
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(0), m_normalsData.jellyPoints.at(0)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(1), m_normalsData.jellyPoints.at(3)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(2), m_normalsData.jellyPoints.at(15)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(3), m_normalsData.jellyPoints.at(12)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(4), m_normalsData.jellyPoints.at(48)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(5), m_normalsData.jellyPoints.at(51)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(6), m_normalsData.jellyPoints.at(63)));
	m_normalsData.frameSprings.emplace_back(Spring(m_normalsData.framePoints.at(7), m_normalsData.jellyPoints.at(60)));
}

const QTimer* Jelly::getPhysicsTimer() const
{
	return m_timerPhysics;
}

const QTimer* Jelly::getDrawTimer() const
{
	return m_timerDraw;
}

const std::vector<JellyPoint>& Jelly::getJellyPoints() const
{
	return m_jellyPoints;
}

void Jelly::updatePhysics()
{
	resetForces();
	for (std::vector<Spring>::iterator springIt = m_frameSprings.begin(); springIt != m_frameSprings.end(); ++springIt)
	{
		QVector3D force = m_physics.calculateSpringsForce(*springIt, m_physics.getC2());
		springIt->applyForce(force);
	}
	for (std::vector<Spring>::iterator springIt = m_springs.begin(); springIt != m_springs.end(); ++springIt)
	{
		QVector3D force = m_physics.calculateSpringsForce(*springIt, m_physics.getC1());
		springIt->applyForce(force);
	}
	for (std::vector<JellyPoint>::iterator jellyIt = m_jellyPoints.begin(); jellyIt != m_jellyPoints.end(); ++jellyIt)
	{
		QVector3D force = m_physics.calculatePointsForce(*jellyIt);
		jellyIt->addForce(force);
		QVector3D velocity = m_physics.calculateVelocity(*jellyIt);
		jellyIt->addVeloctiy(velocity);
		m_physics.calculateBounces(*jellyIt);
		QVector3D position = m_physics.calculatePosition(*jellyIt);
		jellyIt->updatePosition(position);
	}

	for (std::vector<Spring>::iterator springIt = m_normalsData.frameSprings.begin(); springIt != m_normalsData.frameSprings.end(); ++springIt)
	{
		QVector3D force = m_physics.calculateSpringsForce(*springIt, m_physics.getC2());
		springIt->applyForce(force);
	}
	for (std::vector<Spring>::iterator springIt = m_normalsData.springs.begin(); springIt != m_normalsData.springs.end(); ++springIt)
	{
		QVector3D force = m_physics.calculateSpringsForce(*springIt, m_physics.getC1());
		springIt->applyForce(force);
	}
	for (std::vector<JellyPoint>::iterator jellyIt = m_normalsData.jellyPoints.begin(); jellyIt != m_normalsData.jellyPoints.end(); ++jellyIt)
	{
		QVector3D force = m_physics.calculatePointsForce(*jellyIt);
		jellyIt->addForce(force);
		QVector3D velocity = m_physics.calculateVelocity(*jellyIt);
		jellyIt->addVeloctiy(velocity);
		m_physics.calculateBounces(*jellyIt);
		QVector3D position = m_physics.calculatePosition(*jellyIt);
		jellyIt->updatePosition(position);
	}

}

void Jelly::updateFramePosition(std::shared_ptr<CubeFrame> cubeFrame)
{
	std::vector<QVector3D> positions;
	cubeFrame->getVerticesPositions(positions);
	int i = 0;
	for (auto it = m_framePoints.begin(); it != m_framePoints.end(); ++it)
	{
		it->updatePosition(positions.at(i) - it->getPosition());
		++i;
	}
	i = 0;
	for (auto it = m_normalsData.framePoints.begin(); it != m_normalsData.framePoints.end(); ++it)
	{
		//it->updatePosition(positions.at(i) * m_normalsData.factor - it->getPosition());
		it->updatePosition(positions.at(i) - it->getPosition());
		++i;
	}
}

void Jelly::setVelocitiesRange(double velocitiesRange)
{
	m_velocitiesRange = velocitiesRange;
}

void Jelly::setPositionsRange(double positionsRange)
{
	m_positionsRange = positionsRange;
}

void Jelly::setBounceFactor(double bounceFactor)
{
	m_physics.setBounceFactor(bounceFactor);
}

void Jelly::resetForces()
{
	for (auto &jellyPoint : m_jellyPoints)
	{
		jellyPoint.resetForce();
	}
	for (auto &jellyPoint : m_normalsData.jellyPoints)
	{
		jellyPoint.resetForce();
	}
}

QVector<QVector3D> Jelly::getJellyPointsPositions() const
{
	QVector<QVector3D> positions;
	positions.reserve(m_jellyPoints.size());
	for (const auto &jellyPoint : m_jellyPoints)
	{
		positions.push_back(jellyPoint.getPosition());
	}
	return positions;
}

QVector<QVector3D> Jelly::getJellyPointsPositionsNormals() const
{
	QVector<QVector3D> normals;
	normals.reserve(m_normalsData.jellyPoints.size());
	for (int i = 0; i < m_normalsData.jellyPoints.size(); ++i)
	{
		normals.push_back(m_normalsData.jellyPoints[i].getPosition());
	}
	return normals;
}

//QVector<QVector3D> Jelly::getNormals() const
//{
//	QVector<QVector3D> normals;
//	normals.reserve(m_normalsData.jellyPoints.size());
//	for (int i = 0; i < m_normalsData.jellyPoints.size(); ++i)
//	{
//		normals.push_back(QVector3D(m_normalsData.jellyPoints[i].getPosition() - m_jellyPoints[i].getPosition()).normalized());
//	}
//	return normals;
//}

void Jelly::setBoundingX(const QVector2D &boundingX)
{
	m_physics.setBoundingX(boundingX);
}

void Jelly::setBoundingY(const QVector2D &boundingY)
{
	m_physics.setBoundingY(boundingY);
}

void Jelly::setBoundingZ(const QVector2D &boundingZ)
{
	m_physics.setBoundingZ(boundingZ);
}

void Jelly::setk(double k)
{
	m_physics.setFriction(k);
}

void Jelly::setc1(double c1)
{
	m_physics.setElasticityC1(c1);
}

void Jelly::setc2(double c2)
{
	m_physics.setElasticityC2(c2);
}

void Jelly::setMasses(double mass)
{
	m_physics.setMass(mass);
}

void Jelly::randomVelocities()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(-m_velocitiesRange, m_velocitiesRange);
	for (int i = 0; i < m_jellyPoints.size(); ++i)
	{
		QVector3D vel = QVector3D(dist(e2), dist(e2), dist(e2));
		m_jellyPoints[i].setVelocity(vel);
		m_normalsData.jellyPoints[i].setVelocity(vel);
	}
	/*for (auto &jellyPoint : m_jellyPoints)
	{
		jellyPoint.setVelocity(QVector3D(dist(e2), dist(e2), dist(e2)));
	}
	for (auto &jellyPoint : m_normalsData.jellyPoints)
	{
		jellyPoint.setVelocity(QVector3D(dist(e2), dist(e2), dist(e2)));
	}*/
}

void Jelly::randomPositions()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(-m_positionsRange, m_positionsRange);
	for (int i = 0; i < m_jellyPoints.size(); ++i)
	{
		QVector3D pos = QVector3D(dist(e2), dist(e2), dist(e2));
		m_jellyPoints[i].setPosition(pos);
		m_normalsData.jellyPoints[i].setPosition(pos);
	}
	/*for (auto &jellyPoint : m_jellyPoints)
	{
		jellyPoint.updatePosition(QVector3D(dist(e2), dist(e2), dist(e2)));
	}
	for (auto &jellyPoint : m_normalsData.jellyPoints)
	{
		jellyPoint.updatePosition(QVector3D(dist(e2), dist(e2), dist(e2)));
	}*/
}

void Jelly::startSimulation()
{
	m_timerPhysics->start(m_physicsStep);
	m_timerDraw->start(m_drawStep);
	m_simulate = true;
}
