#pragma once
#include "JellyPoint.h"

class Spring
{
public:
	Spring(JellyPoint &p1, JellyPoint &p2);
	~Spring();

	float getInitialLength() const;
	float getCurrLength() const;
	const JellyPoint& getPoint(bool first) const;
	void applyForce(const QVector3D &force);
	void setInitialLength(float length);
	void setInitialLength(const QVector3D &p1, const QVector3D &p2);

private:
	JellyPoint &m_p1, &m_p2;
	float m_initialLength;
};
