#include "BezierCube.h"

BezierCube::BezierCube(GLenum drawMode, int index, int divisions = 32, QVector3D color = QVector3D(0, 0, 1))
	: Mesh(drawMode, index), m_divisions(divisions), m_color(color)
{
	BezierCube::generateVertices();
	BezierCube::generateIndices();
	fillPositions();
}

BezierCube::BezierCube(const QVector<Vertex>& vertices, const QVector<GLushort>& indices, GLenum drawMode, int index, QVector3D color)
	: Mesh(vertices, indices, drawMode, index), m_divisions(0), m_color(color)
{
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

	for (int z = 0; z <= m_divisions; z += m_divisions - 1)
	{
		float az = distance * z;
		float norm;
		if (az < 0.1f)
			norm = -1;
		else
			norm = 1;
		for (int y = 0; y < m_divisions; ++y)
		{
			float ay = distance * y;
			for (int x = 0; x < m_divisions; ++x)
			{
				float ax = distance * x;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D(0,0,norm)));
			}
		}
	}
	for (int y = 0; y <= m_divisions; y += m_divisions - 1)
	{
		float ay = distance * y;
		float norm; 
		if (ay < 0.1f)
			norm = -1;
		else
			norm = 1;
		for (int z = 0; z < m_divisions; ++z)
		{
			float az = distance * z;
			for (int x = 0; x < m_divisions; ++x)
			{
				float ax = distance * x;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D(0, norm, 0)));
			}
		}
	}
	for (int x = 0; x <= m_divisions; x += m_divisions - 1)
	{
		float ax = distance * x;
		float norm;
		if (ax < 0.1f)
			norm = -1;
		else
			norm = 11;
		for (int y = 0; y < m_divisions; ++y)
		{
			float ay = distance * y;
			for (int z = 0; z < m_divisions; ++z)
			{
				float az = distance * z;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D(norm, 0, 0)));
			}
		}
	}
}

void BezierCube::generateIndices()
{
	for (int j = 0; j < m_divisions * (m_divisions - 1); j+=m_divisions)
	{
		for (int i = 0; i < (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions + 1);
			m_indices.push_back(j + i + m_divisions);
		}
	}
	int pointsInd = m_divisions * m_divisions;
	for (int j = 0; j < m_divisions * (m_divisions - 1); j += m_divisions)
	{
		for (int i = pointsInd; i < pointsInd + (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + m_divisions + 1);
		}
	}

	pointsInd += m_divisions * m_divisions;
	for (int j = 0; j < m_divisions * (m_divisions - 1); j += m_divisions)
	{
		for (int i = pointsInd; i < pointsInd + (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + m_divisions + 1);
		}
	}

	pointsInd += m_divisions * m_divisions;
	for (int j = 0; j < m_divisions * (m_divisions - 1); j += m_divisions)
	{
		for (int i = pointsInd; i < pointsInd + (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions + 1);
			m_indices.push_back(j + i + m_divisions);
		}
	}

	pointsInd += m_divisions * m_divisions;
	for (int j = 0; j < m_divisions * (m_divisions - 1); j += m_divisions)
	{
		for (int i = pointsInd; i < pointsInd + (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + m_divisions + 1);
		}
	}

	pointsInd += m_divisions * m_divisions;
	for (int j = 0; j < m_divisions * (m_divisions - 1); j += m_divisions)
	{
		for (int i = pointsInd; i < pointsInd + (m_divisions - 1); ++i)
		{
			m_indices.push_back(j + i);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions);
			m_indices.push_back(j + i + 1);
			m_indices.push_back(j + i + m_divisions + 1);
			m_indices.push_back(j + i + m_divisions);
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
