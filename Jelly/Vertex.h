#pragma once
#include <QVector3D>

class Vertex
{
public:
	Vertex();
	explicit Vertex(const QVector3D &position);
	Vertex(const QVector3D &position, const QVector3D &color, const QVector3D &normal);

	static const int PositionTupleSize = 3;
	static const int ColorTupleSize = 3;
	static const int NormalTupleSize = 3;

	const QVector3D &getPosition() const;
	const QVector3D &getColor() const;
	const QVector3D &getNormal() const;
	void setPosition(QVector3D &position);
	void setColor(QVector3D &color);
	void setNormal(QVector3D &normal);
	static int getPositionOffset();
	static int getColorOffset();
	static int getNormalOffset();
	static int getStride();

private:
	QVector3D m_position;
	QVector3D m_color;
	QVector3D m_normal;
};