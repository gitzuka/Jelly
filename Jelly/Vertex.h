#pragma once
#include <QVector3D>

class Vertex
{
public:
	Vertex();
	explicit Vertex(const QVector3D &position);
	Vertex(const QVector3D &position, const QVector3D &color, const QVector3D &normal);

	static const int PositionColorNormalTupleSize = 3;

	const QVector3D &getPosition() const;
	const QVector3D &getColor() const;
	const QVector3D &getNormal() const;
	const QVector3D &getPositionNormal() const;
	void setPosition(const QVector3D &position);
	void setColor(const QVector3D &color);
	void setNormal(const QVector3D &normal);
	void setPositionNormal(const QVector3D &positionNormal);
	static int getPositionOffset();
	static int getColorOffset();
	static int getNormalOffset();
	static int getPositionNormalOffset();
	static int getStride();

private:
	QVector3D m_position;
	QVector3D m_color;
	QVector3D m_normal;
	QVector3D m_positionNormal;
};