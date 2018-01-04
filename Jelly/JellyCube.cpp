#include "JellyCube.h"

JellyCube::JellyCube(GLenum drawMode, int index, QVector3D color = QVector3D(0, 1.0f, 1.0f), float edgeLength = 0.1f)
	: Mesh(drawMode, index), m_edgeLength(edgeLength), m_color(color)
{
	JellyCube::generateVertices();
	//generateSprings();
}

JellyCube::~JellyCube()
{
}

void JellyCube::generateVertices()
{
	int verticesNum = 64;
	m_vertices.reserve(verticesNum);

	for (int z = 0; z < 4; ++z)
	{
		float az = -m_edgeLength / 2.0f + 1 / 3.0f * m_edgeLength * z;
		for (int y = 0; y < 4; ++y)
		{
			float ay = m_edgeLength / 2.0f - 1 / 3.0f * m_edgeLength * y;
			for (int x = 0; x < 4; ++x)
			{
				float ax = -m_edgeLength / 2.0f + 1 / 3.0f * m_edgeLength * x;
				m_vertices.push_back(Vertex(QVector3D(ax, ay, az), m_color, QVector3D()));
			}
		}
	}
}

void JellyCube::generateIndices()
{
}

void JellyCube::generateSprings(std::vector<Spring> &springs, std::vector<JellyPoint> &jellyPoints)
{
	generateJellyPoints(jellyPoints);
	m_indices.reserve(360);
	springs.reserve(360);
	for (int z = 0; z < 4; ++z) //create springs along x axis
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				int index = 16 * z + 4 * y + x;
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 1)));
				m_indices.push_back(index);
				m_indices.push_back(index + 1);
				if (y == 3)
				{
					continue;
				}
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 5)));
				springs.push_back(Spring(jellyPoints.at(index + 1), jellyPoints.at(index + 4)));
				m_indices.push_back(index);
				m_indices.push_back(index + 5);
				m_indices.push_back(index + 1);
				m_indices.push_back(index + 4);
			}
		}
	}
	for (int z = 0; z < 4; ++z) //create springs along y axis
	{
		for (int x = 0; x < 4; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				int index = 16 * z + x + 4 * y;
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 4)));
				m_indices.push_back(index);
				m_indices.push_back(index + 4);
				if (z == 3)
				{
					continue;
				}
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 20)));
				springs.push_back(Spring(jellyPoints.at(index + 4), jellyPoints.at(index + 16)));
				m_indices.push_back(index);
				m_indices.push_back(index + 20);
				m_indices.push_back(index + 4);
				m_indices.push_back(index + 16);

			}
		}
	}
	for (int x = 0; x < 4; ++x) //create springs along z axis
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int z = 0; z < 3; ++z)
			{
				int index = 16 * z + 4 * y + x;
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 16)));
				m_indices.push_back(index);
				m_indices.push_back(index + 16);
				if (x == 3)
				{
					continue;
				}
				springs.push_back(Spring(jellyPoints.at(index), jellyPoints.at(index + 17)));
				springs.push_back(Spring(jellyPoints.at(index + 1), jellyPoints.at(index + 16)));
				m_indices.push_back(index);
				m_indices.push_back(index + 17);
				m_indices.push_back(index + 1);
				m_indices.push_back(index + 16);
			}
		}
	}
}

void JellyCube::generateFrameSprings(std::vector<Spring> &springs, std::vector<JellyPoint> &jellyPoints)
{
	springs.reserve(8);
	jellyPoints.reserve(8);
}

void JellyCube::generateJellyPoints(std::vector<JellyPoint>& jellyPoints)
{
	jellyPoints.clear();
	jellyPoints.reserve(m_vertices.count());
	for (QVector<Vertex>::const_iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		jellyPoints.push_back(JellyPoint((*it).getPosition(), 1.0f, QVector3D(0, 0, 0)));
	}
}

void JellyCube::setEdgeLength(float edgeLength)
{
	m_edgeLength = edgeLength;
}

void JellyCube::updateVerticesPositions(const std::vector<JellyPoint>& positions)
{
	QVector<Vertex>::iterator vit = m_vertices.begin();
	std::vector<JellyPoint>::const_iterator it = positions.begin();
	for (it = positions.begin();( it != positions.end() || vit != m_vertices.end()); ++it, ++vit)
	{
		vit->setPosition(it->getPosition());
	}
}
