#pragma once
#include "JellyCube.h"
#include "CubeFrame.h"
#include <memory>
#include "Physics.h"
#include "Graphics.h"
#include <qtimer.h>

struct JellyNormalsData
{
	std::vector<JellyPoint> jellyPoints;
	std::vector<JellyPoint> framePoints;
	std::vector<Spring> frameSprings; 
	std::vector<Spring> springs;
	float factor = 2.f;
};

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
	QVector<QVector3D> getJellyPointsPositions() const;
	QVector<QVector3D> getJellyPointsPositionsNormals() const;
	//QVector<QVector3D> getNormals() const;
	void setBoundingX(const QVector2D &boundingX);
	void setBoundingY(const QVector2D &boundingY);
	void setBoundingZ(const QVector2D &boundingZ);

private:
	Physics m_physics;
	JellyNormalsData m_normalsData;
	std::vector<Spring> m_springs;
	//first point is frame point, position isnt affected by physics
	std::vector<Spring> m_frameSprings; 
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
	void setBounceFactor(double bounceFactor);
};
