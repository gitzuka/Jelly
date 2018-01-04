#include "BezierCube.h"

BezierCube::BezierCube(GLenum drawMode, int index, int divisions = 32, QVector3D color = QVector3D(0, 0, 1))
	: Mesh(drawMode, index), m_divisions(divisions), m_color(color)
{
	BezierCube::generateVertices();
	BezierCube::generateIndices();
	fillPositions();
}

BezierCube::~BezierCube()
{
}

void BezierCube::generateVertices()
{
	m_vertices.reserve(m_divisions * m_divisions * m_divisions);
	float edgeLength = 1.0f;
	float distance = 1.0f / (m_divisions - 1) * edgeLength;
	//for (int z = 0; z < m_divisions; ++z)
	//{
	//	float az = distance * z;
	//	for (int y = 0; y < m_divisions; ++y)
	//	{
	//		float ay = distance * y;
	//		for (int x = 0; x < m_divisions; ++x)
	//		{
	//			float ax = distance * x;
	//			m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
	//		}
	//	}
	//}
	///////////////
	for (int z = 0; z <= m_divisions; z += m_divisions - 1)
	{
		float az = distance * z;
		for (int y = 0; y < m_divisions; ++y)
		{
			float ay = distance * y;
			for (int x = 0; x < m_divisions; ++x)
			{
				float ax = distance * x;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
			}
		}
	}
	for (int y = 0; y <= m_divisions; y += m_divisions - 1)
	{
		float ay = distance * y;
		for (int z = 0; z < m_divisions; ++z)
		{
			float az = distance * z;
			for (int x = 0; x < m_divisions; ++x)
			{
				float ax = distance * x;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
			}
		}
	}
	for (int x = 0; x <= m_divisions; x += m_divisions - 1)
	{
		float ax = distance * x;
		for (int y = 0; y < m_divisions; ++y)
		{
			float ay = distance * y;
			for (int z = 0; z < m_divisions; ++z)
			{
				float az = distance * z;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
			}
		}
	}

	//for (int z = 0; z < m_divisions; ++z)
	//{
	//	float az = distance * z;
	//	for (int y = 0; y < m_divisions; ++y)
	//	{
	//		float ay = distance * y;
	//		for (int x = 0; x <= m_divisions; x+=m_divisions-1)
	//		{
	//			float ax = distance * x;
	//			m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
	//		}
	//	}
	//}
}

void BezierCube::generateIndices()
{
	//for (int i =0; i<m_vertices.count(); ++i)
	//{
	//	m_indices.push_back(i);

	//	//m_indices.push_back(i + 1);
	//}
	//m_indices.reserve(m_vertices.count() * 2);
	//m_indices.reserve(m_vertices.count() * 3);
	//for (int i =0; i<m_vertices.count(); ++i)
	//{
	//	m_indices.push_back(i);
	//	m_indices.push_back(i + 1);
	//	m_indices.push_back(i + 32);
	//	m_indices.push_back(i + 1);
	//	m_indices.push_back(i + 33);
	//	m_indices.push_back(i + 32);

	//	//m_indices.push_back(i + 1);
	//}
	////
	for (int j = 0; j < 32 * 31; j+=32)
	{
		for (int i = 0; i < 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 33);
			m_indices.push_back(j + i + 32);
		}
	}
	for (int j = 0; j < 32 * 31; j += 32)
	{
		for (int i = 1024; i < 1024 + 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 33);
		}
	}

	for (int j = 0; j < 32 * 31; j += 32)
	{
		for (int i = 2048; i < 2048 + 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 33);
		}
	}
	for (int j = 0; j < 32 * 31; j += 32)
	{
		for (int i = 3072; i < 3072 + 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 33);
			m_indices.push_back(j + i + 32);
		}
	}

	for (int j = 0; j < 32 * 31; j += 32)
	{
		for (int i = 4096; i < 4096 + 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 33);
		}
	}
	for (int j = 0; j < 32 * 31; j += 32)
	{
		for (int i = 5120; i < 5120 + 31; ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 32);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 33);
			m_indices.push_back(j + i + 32);
		}
	}
}

const QVector<QVector3D>& BezierCube::getPositions() const
{
	return m_positions;
}

void BezierCube::fillPositions()
{
	m_positions.reserve(m_vertices.count());
	for (QVector<Vertex>::const_iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		m_positions.push_back(it->getPosition());
	}
}
