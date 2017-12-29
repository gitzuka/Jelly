#include "Jelly.h"
#include <random>

//Jelly::Jelly(std::shared_ptr<Graphics> jellyMesh) : m_jellyGraphics(jellyMesh)
Jelly::Jelly() : m_physicsStep(5), m_drawStep(100), m_timerPhysics(new QTimer(this)), m_timerDraw(new QTimer(this)), m_simulate(false)
{
}

Jelly::~Jelly()
{
}

void Jelly::createSpringsAndPoints(std::shared_ptr<JellyCube> jellyCube)
{
	jellyCube->generateSprings(m_springs, m_jellyPoints);
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
	for (std::vector<Spring>::iterator springIt = m_springs.begin(); springIt != m_springs.end(); ++springIt)
	{
		QVector3D force = m_physics.calculateSpringsForce(*springIt);
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

void Jelly::resetForces()
{
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->resetForce();
	}
}

//void Jelly::calculateForces()
//{
//	for (std::vector<Spring>::iterator springIt = m_springs.begin(); springIt != m_springs.end(); ++springIt)
//	{
//		QVector3D force = m_physics.calculateSpringsForce(*springIt);
//		springIt->applyForce(force);
//	}
//	for (std::vector<JellyPoint>::iterator jellyIt = m_jellyPoints.begin(); jellyIt != m_jellyPoints.end(); ++jellyIt)
//	{
//		QVector3D force = m_physics.calculatePointsForce(*jellyIt);
//		jellyIt->addForce(force);
//		QVector3D velocity = m_physics.calculateVelocity(*jellyIt);
//		jellyIt->addVeloctiy(velocity);
//		QVector3D position = m_physics.calculatePosition(*jellyIt);
//		jellyIt->updatePosition(position);
//	}
//}
//
//void Jelly::calculateVelocities()
//{
//
//}
//
//void Jelly::calculatePositions()
//{
//}

void Jelly::connectToGraphics(std::shared_ptr<Graphics> jellyGraphics)
{
	//connect(this, SIGNAL(simulationUpdated(int)), jellyGraphics.get(), SLOT(m_jellyGraphics->updateJellyData(int)));
}

void Jelly::setk(double k)
{
	m_physics.setFriction(k);
}

void Jelly::setc1(double c1)
{
	m_physics.setElasticity(c1);
}

void Jelly::setMasses(double mass)
{
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->setMass(mass);
	}
}

void Jelly::randomVelocities()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0.01, 0.1);
	for (std::vector<JellyPoint>::iterator it = m_jellyPoints.begin(); it != m_jellyPoints.end(); ++it)
	{
		it->setVelocity(QVector3D(dist(e2), dist(e2), dist(e2)));
	}
}

void Jelly::startSimulation()
{
	m_timerPhysics->start(m_physicsStep);
	m_timerDraw->start(m_drawStep);
	m_simulate = true;
}
