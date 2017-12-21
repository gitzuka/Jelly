#include "Graphics.h"

Graphics::Graphics(QOpenGLShaderProgram* program) : m_program(program)
{
}

Graphics::~Graphics()
{
	m_vao.destroy();
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_vbos.at(i).destroy();
		m_ibos.at(i).destroy();
	}
	delete m_program;
}

void Graphics::initBuffer()
{
	m_program->bind();
	
	m_vbos.reserve(m_meshes.size());
	m_ibos.reserve(m_meshes.size());
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		if (!m_vao.isCreated())
		{
			m_vao.create();
		}
		m_vao.bind(); 
		m_vbos.push_back(QOpenGLBuffer());
		m_vbos.at(i).create();
		m_vbos.at(i).bind();
		m_vbos.at(i).setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vbos.at(i).allocate(m_meshes.at(i)->getVertices().constData(), m_meshes.at(i)->getVertices().count() * sizeof(Vertex));

		m_ibos.push_back(QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
		m_ibos.at(i).create();
		m_ibos.at(i).bind();
		m_ibos.at(i).setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_ibos.at(i).allocate(m_meshes.at(i)->getIndices().constData(), m_meshes.at(i)->getIndices().size() * sizeof(GLushort));
		
		m_program->enableAttributeArray(0);
		m_program->enableAttributeArray(1);
		m_program->enableAttributeArray(2);

		m_vao.release();
		m_ibos.at(i).release();
		m_vbos.at(i).release();
	}
	m_program->release();
}

void Graphics::updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex)
{
	m_vbos.at(bufferIndex).bind();
	m_vbos.at(bufferIndex).write(offset * sizeof(Vertex), vertex, sizeof(QVector3D));
	m_vbos.at(bufferIndex).release();
}

void Graphics::addMesh(const std::shared_ptr<Mesh> mesh)
{
	m_meshes.append(mesh);
}

void Graphics::assignShaderProgram(QOpenGLShaderProgram* program)
{
	m_program = program;
}

const QVector<std::shared_ptr<Mesh>>& Graphics::getMeshes() const
{
	return m_meshes;
}

void Graphics::draw(const QMatrix4x4 &projView)
{
	m_program->bind();
	int i = 0;
	for (QVector<std::shared_ptr<Mesh>>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
	{
		m_program->setUniformValue(m_program->uniformLocation("MVP"), projView * (*it)->getModelMatrix());
		m_vao.bind();
		m_vbos.at(i).bind();
		m_ibos.at(i).bind();

		m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::getPositionOffset(), Vertex::PositionTupleSize, Vertex::getStride());
		m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::getNormalOffset(), Vertex::NormalTupleSize, Vertex::getStride());
		m_program->setAttributeBuffer(2, GL_FLOAT, Vertex::getColorOffset(), Vertex::ColorTupleSize, Vertex::getStride());
		glDrawElements((*it)->getDrawMode(), (*it)->getIndices().size(), GL_UNSIGNED_SHORT, nullptr);
		m_ibos.at(i).release();
		m_vbos.at(i).release();
		m_vao.release();
		++i;
	}
	m_program->release();
}
