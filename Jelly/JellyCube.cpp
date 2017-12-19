#include "JellyCube.h"

JellyCube::JellyCube(GLenum drawMode, QVector3D color = QVector3D(0, 1.0f, 1.0f), float edgeLength = 0.1f)
	: Mesh(drawMode), m_edgeLength(edgeLength), m_color(color)
{
	JellyCube::generateVertices();
	generateSprings();
}

JellyCube::~JellyCube()
{
}

void JellyCube::generateVertices()
{
	int verticesNum = 64;
	std::vector<QVector3D> cubePos;
	cubePos.reserve(verticesNum);

	for (int z = 0; z < 4; ++z)
	{
		float az = -m_edgeLength / 2.0f + 1 / 3.0f * m_edgeLength * z;
		for (int y = 0; y < 4; ++y)
		{
			float ay = m_edgeLength / 2.0f - 1 / 3.0f * m_edgeLength * y;
			for (int x = 0; x < 4; ++x)
			{
				float ax = -m_edgeLength / 2.0f + 1 / 3.0f * m_edgeLength * x;
				cubePos.push_back(QVector3D(ax, ay, az));
			}
		}
	}

	m_vertices.reserve(verticesNum);
	for (int i = 0; i < verticesNum; ++i)
	{
		m_vertices.push_back(Vertex(cubePos.at(i), m_color, QVector3D()));
	}

}

void JellyCube::generateSprings()
{
	int verticesNum = 64;
	for (int z = 0; z < 4; ++z) //create springs along x axis
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				int index = 16 * z + 4 * y + x;
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 1)));
				if (y == 3)
				{
					continue;
				}
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 5)));
				m_springs.push_back(Spring(m_vertices.at(index + 1), m_vertices.at(index + 4)));
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
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 4)));
				if (z == 3)
				{
					continue;
				}
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 20)));
				m_springs.push_back(Spring(m_vertices.at(index + 4), m_vertices.at(index + 16)));
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
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 16)));
				if (x == 3)
				{
					continue;
				}
				m_springs.push_back(Spring(m_vertices.at(index), m_vertices.at(index + 17)));
				m_springs.push_back(Spring(m_vertices.at(index + 1), m_vertices.at(index + 16)));
			}
		}
	}
}

void JellyCube::setEdgeLength(float edgeLength)
{
	m_edgeLength = edgeLength;
}
