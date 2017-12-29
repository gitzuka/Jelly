#pragma once
#include "JellyPoint.h"

class Spring
{
public:
	//Spring(const QVector3D &p1, const QVector3D &p2);
	Spring(JellyPoint &p1, JellyPoint &p2);
	//Spring();
	~Spring();

	float getInitialLength() const;
	float getCurrLength() const;
	//float getElasticity() const;
	const JellyPoint& getPoint(bool first) const;
	void applyForce(const QVector3D &force);
	void setInitialLength(float length);
	//void setElasticity(float elasticity);
	//void setCurrLength(float length);
	void setInitialLength(const QVector3D &p1, const QVector3D &p2);
	//void setCurrLength(const QVector3D &p1, const QVector3D &p2);

private:
	JellyPoint &m_p1, &m_p2;
	float m_initialLength;
	//float m_currLength;
	//float m_elasticity; //c1 from 
};
