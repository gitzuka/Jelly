#pragma once
#include <QVector3D>
#include <qvector2d.h>

class JellyPoint;
class Spring;

class Physics
{
public:
	Physics();
	~Physics();

	QVector3D calculateSpringsForce(const Spring &spring, float c) const;
	QVector3D calculatePointsForce(const JellyPoint &point) const;
	QVector3D calculatePosition(const JellyPoint &point) const;
	QVector3D calculateVelocity(const JellyPoint &point) const;
	QVector3D calculateBounces(JellyPoint &point) const;
	float getC1() const;
	float getC2() const;

	void setFriction(double friction);
	void setMass(double mass);
	void setElasticityC1(double elasticity);
	void setElasticityC2(double elasticity);
	void setBoundingX(const QVector2D &boundingX);
	void setBoundingY(const QVector2D &boundingY);
	void setBoundingZ(const QVector2D &boundingZ);
	void setBounceFactor(double bounceFactor);

private:
	float m_k; //friction
	float m_c1; //elasticity of jelly's springs
	float m_c2; //elasticity of frame springs
	float m_deltaTime;
	float m_mass;
	float m_bounceElasticity;
	int m_maxStep;
	QVector2D m_boundingX;
	QVector2D m_boundingY;
	QVector2D m_boundingZ;

	QVector3D calculateElasticBounce(JellyPoint &point) const;
	QVector3D calculateNonElasticBounce(JellyPoint &point) const;
	//direction from point p1 to p2
	QVector3D getDirectionVec(const QVector3D &p1, const QVector3D &p2) const;
};
