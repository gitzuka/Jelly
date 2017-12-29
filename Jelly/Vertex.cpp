#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(const QVector3D &position) : m_position(position)
{
}

Vertex::Vertex(const QVector3D &position, const QVector3D &color, const QVector3D &normal)
	: m_position(position), m_color(color), m_normal(normal)
{
}

const QVector3D &Vertex::getPosition() const
{
	return  m_position;
}

const QVector3D &Vertex::getColor() const
{
	return m_color;
}

const QVector3D & Vertex::getNormal() const
{
	return m_normal;
}

void Vertex::setPosition(const QVector3D &position)
{
	m_position = position;
}

void Vertex::setColor(const QVector3D &color)
{
	m_color = color;
}

void Vertex::setNormal(const QVector3D &normal)
{
	m_normal = normal;
}

int Vertex::getPositionOffset()
{
	return offsetof(Vertex, m_position);
}

int Vertex::getColorOffset()
{
	return offsetof(Vertex, m_color);
}

int Vertex::getNormalOffset()
{
	return offsetof(Vertex, m_normal);
}

int Vertex::getStride()
{
	return sizeof(Vertex);
}
