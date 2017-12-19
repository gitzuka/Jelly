#include "Graphics.h"

Graphics::Graphics(const QVector<Mesh> &meshes) : m_meshes(meshes)
{
}

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	m_vao.destroy();
	for (int i = 0; i < m_vertexBuffers.size(); ++i)
	{
		m_vertexBuffers.at(i).destroy();
	}
}

void Graphics::initBuffer(QOpenGLShaderProgram *program)
{
	program->bind();

	//for (std::vector<QOpenGLBuffer>::iterator it = m_vertexBuffers.begin(); it != m_vertexBuffers.end(); ++it)
	for (int i = 0; i < m_vertexBuffers.size(); ++i)
	{
		if (m_vertexBuffers.at(i).isCreated())
		{
			continue;
		}
		m_vertexBuffers.at(i).create();
		m_vertexBuffers.at(i).bind();
		m_vertexBuffers.at(i).create();
		m_vertexBuffers.at(i).create();
		m_vertexBuffers.at(i).setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vertexBuffers.at(i).allocate(m_meshes.at(i).getVertices().constData(), m_meshes.at(i).getVertices().count() * sizeof(Vertex));

		if (!m_vao.isCreated())
		{
			m_vao.create();
		}
		m_vao.bind();

		program->enableAttributeArray(0);
		program->enableAttributeArray(1);
		program->enableAttributeArray(2);

		program->setAttributeBuffer(0, GL_FLOAT, Vertex::getPositionOffset(), Vertex::PositionTupleSize, Vertex::getStride());
		program->setAttributeBuffer(1, GL_FLOAT, Vertex::getNormalOffset(), Vertex::NormalTupleSize, Vertex::getStride());
		program->setAttributeBuffer(2, GL_FLOAT, Vertex::getColorOffset(), Vertex::ColorTupleSize, Vertex::getStride());

		m_vao.release();
		m_vertexBuffers.at(i).release();
	}
	program->release();
}

void Graphics::updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex)
{
	m_vertexBuffers.at(bufferIndex).bind();
	m_vertexBuffers.at(bufferIndex).write(offset * sizeof(Vertex), vertex, sizeof(QVector3D));
	m_vertexBuffers.at(bufferIndex).release();
}

void Graphics::addMesh(const Mesh &mesh)
{
	m_meshes.append(mesh);
}

QOpenGLVertexArrayObject *Graphics::getVao()
{
	return &m_vao;
}

const QVector<Mesh>& Graphics::getMeshes() const
{
	return m_meshes;
}
