#pragma once
#include <QVector3D>

class JellyPoint;
class Spring;

class Physics
{
public:
	Physics();
	~Physics();

	QVector3D calculateSpringsForce(const Spring &spring) const;
	QVector3D calculatePointsForce(const JellyPoint &point) const;
	QVector3D calculatePosition(const JellyPoint &point) const;
	QVector3D calculateVelocity(const JellyPoint &point) const;
	void update(const std::vector<Spring> &springs, std::vector<JellyPoint> &points);

	void setFriction(double friction);
	void setElasticity(double elasticity);
	
	//direction from point p1 to p2
	QVector3D getDirectionVec(const QVector3D &p1, const QVector3D &p2) const;

private:
	double m_k; //friction
	double m_c1; //elasticity of jelly's springs
	float m_deltaTime;

	//void updateAcceleration() const;
};
