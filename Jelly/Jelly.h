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
	//explicit Jelly(std::shared_ptr<Graphics> jellyMesh);
	Jelly();
	virtual ~Jelly();
	
	void createSpringsAndPoints(std::shared_ptr<JellyCube> jellyCube);
	const QTimer* getPhysicsTimer() const;
	const QTimer* getDrawTimer() const;
	const std::vector<JellyPoint>& getJellyPoints() const;
	void startSimulation();
	//void addJellyMesh(std::shared_ptr<JellyCube> jellyMesh);
	//void addJellyGraphics(std::shared_ptr<Graphics> jellyMesh);
	//void addJellyCubeFrame(std::shared_ptr<CubeFrame> jellyMesh);

private:
	//std::shared_ptr<JellyCube> m_jellyMesh;
	//std::shared_ptr<Graphics> m_jellyGraphics;
	//std::shared_ptr<CubeFrame> m_frameMesh;
	Physics m_physics;
	std::vector<Spring> m_springs;
	std::vector<Spring> m_frameSprings;
	std::vector<JellyPoint> m_framePoints;
	std::vector<JellyPoint> m_jellyPoints;
	float m_mass;
	int m_physicsStep;
	int m_drawStep;
	QTimer *m_timerPhysics;
	QTimer *m_timerDraw;
	bool m_simulate;
	//int m_calculationCycles;

	void resetForces();
	/*void calculateForces();
	void calculateVelocities();
	void calculatePositions();*/
	void connectToGraphics(std::shared_ptr<Graphics> jellyGraphics);

signals:
	void simulationUpdated(int jellyIndex);

public slots:
	void setk(double k);
	void setc1(double c1);
	void setMasses(double mass);
	void randomVelocities();
	void updatePhysics();
};
