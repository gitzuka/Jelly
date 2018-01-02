#include "Jelly.h"
#include <random>

Jelly::Jelly() 
	: m_velocitiesRange(0), m_positionsRange(0), m_physicsStep(3), m_drawStep(30), 
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
	m_framePoints.reserve(8);
	for (std::vector<QVector3D>::const_iterator it = framePositions.begin(); it != framePositions.end(); ++it)
	{
		m_framePoints.push_back(JellyPoint(*it, 1.0f, QVector3D(0,0,0)));
	}
	m_frameSprings.reserve(8);
	m_frameSprings.push_back(Spring(m_framePoints.at(0), m_jellyPoints.at(0)));
	m_frameSprings.push_back(Spring(m_framePoints.at(1), m_jellyPoints.at(3)));
	m_frameSprings.push_back(Spring(m_framePoints.at(2), m_jellyPoints.at(15)));
	m_frameSprings.push_back(Spring(m_framePoints.at(3), m_jellyPoints.at(12)));
	m_frameSprings.push_back(Spring(m_framePoints.at(4), m_jellyPoints.at(48)));
	m_frameSprings.push_back(Spring(m_framePoints.at(5), m_jellyPoints.at(51)));
	m_frameSprings.push_back(Spring(m_framePoints.at(6), m_jellyPoints.at(63)));
	m_frameSprings.push_back(Spring(m_framePoints.at(7), m_jellyPoints.at(60)));
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
		QVector3D position = m_physics.calculatePosition(*jellyIt);
		jellyIt->updatePosition(position);
	}
}

void Jelly::updateFramePosition(std::shared_ptr<CubeFrame> cubeFrame)
{
	std::vector<QVector3D> positions;
	cubeFrame->getVerticesPositions(positions);
	int i = 0;
	for (std::vector<JellyPoint>::iterator it = m_framePoints.begin(); it != m_framePoints.end(); ++it)
	{
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

void Jelly::resetForces()
{
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->resetForce();
	}
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
	/*for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->setMass(mass);
	}*/
}

void Jelly::randomVelocities()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(-m_velocitiesRange, m_velocitiesRange);
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->setVelocity(QVector3D(dist(e2), dist(e2), dist(e2)));
	}
}

void Jelly::randomPositions()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(-m_positionsRange, m_positionsRange);
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->updatePosition(QVector3D(dist(e2), dist(e2), dist(e2)));
	}
}

void Jelly::startSimulation()
{
	m_timerPhysics->start(m_physicsStep);
	m_timerDraw->start(m_drawStep);
	m_simulate = true;
}
