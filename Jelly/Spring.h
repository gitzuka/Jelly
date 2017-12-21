#pragma once
#include "JellyPoint.h"

class Spring
{
public:
	Spring(const QVector3D &p1, const QVector3D &p2);
	//Spring();
	~Spring();

	float getInitialLength() const;
	float getCurrLength() const;
	const JellyPoint& getPoint(bool first) const;
	void setInitialLength(float length);
	void setCurrLength(float length);
	void setInitialLength(const QVector3D &p1, const QVector3D &p2);
	void setCurrLength(const QVector3D &p1, const QVector3D &p2);

private:
	float m_initialLength;
	float m_currLength;
	JellyPoint m_p1, m_p2;
};
