#pragma once
#include "JellyCube.h"
#include "CubeFrame.h"
#include <memory>
#include "Physics.h"
#include "Graphics.h"
#include <qtimer.h>

class Jelly : public QObject
{
	Q_OBJECT
public:
	Jelly();
	virtual ~Jelly();
	
	void createSpringsAndPoints(std::shared_ptr<JellyCube> jellyCube, std::shared_ptr<CubeFrame> cubeFrame);
	const QTimer* getPhysicsTimer() const;
	const QTimer* getDrawTimer() const;
	const std::vector<JellyPoint>& getJellyPoints() const;
	void startSimulation();

private:
	Physics m_physics;
	std::vector<Spring> m_springs;
	std::vector<Spring> m_frameSprings; //first point is frame point, position isnt affected by physics
	std::vector<JellyPoint> m_framePoints;
	std::vector<JellyPoint> m_jellyPoints;
	float m_velocitiesRange;
	float m_positionsRange;
	int m_physicsStep;
	int m_drawStep;
	QTimer *m_timerPhysics;
	QTimer *m_timerDraw;
	bool m_simulate;

	void resetForces();

signals:
	void simulationUpdated(int jellyIndex);

private slots:
	void setk(double k);
	void setc1(double c1);
	void setc2(double c2);
	void setMasses(double mass);
	void randomVelocities();
	void randomPositions();
	void updatePhysics();
	void updateFramePosition(std::shared_ptr<CubeFrame> cubeFrame);
	void setVelocitiesRange(double velocitiesRange);
	void setPositionsRange(double positionsRange);
};
