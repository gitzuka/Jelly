#include "Graphics.h"
#include "JellyPoint.h"
#include "JellyCube.h"
#include "BezierCube.h"

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

void Graphics::initBuffers()
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

void Graphics::initBuffer(QOpenGLBuffer* vertBuffer, QOpenGLBuffer* indexBuffer, QOpenGLBuffer::UsagePattern bufferUsage, std::shared_ptr<Mesh> mesh)
{
	m_program->bind();

	if (!m_vao.isCreated())
	{
		m_vao.create();
	}
	m_vao.bind();
	vertBuffer->create();
	vertBuffer->bind();
	vertBuffer->setUsagePattern(bufferUsage);
	vertBuffer->allocate(mesh->getVertices().constData(), mesh->getVertices().count() * sizeof(Vertex));

	indexBuffer->create();
	indexBuffer->bind();
	indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
	indexBuffer->allocate(mesh->getIndices().constData(), mesh->getIndices().size() * sizeof(GLushort));

	m_program->enableAttributeArray(0);
	m_program->enableAttributeArray(1);
	m_program->enableAttributeArray(2);

	m_vao.release();
	vertBuffer->release();
	indexBuffer->release();
	m_program->release();
}

void Graphics::initBuffer(int bufferIndex, QOpenGLBuffer::UsagePattern bufferUsage)
{
	m_program->bind();

		if (!m_vao.isCreated())
		{
			m_vao.create();
		}
		m_vao.bind();
		m_vbos.push_back(QOpenGLBuffer());
		m_vbos.at(bufferIndex).create();
		m_vbos.at(bufferIndex).bind();
		m_vbos.at(bufferIndex).setUsagePattern(bufferUsage);
		m_vbos.at(bufferIndex).allocate(m_meshes.at(bufferIndex)->getVertices().constData(), m_meshes.at(bufferIndex)->getVertices().count() * sizeof(Vertex));

		m_ibos.push_back(QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
		m_ibos.at(bufferIndex).create();
		m_ibos.at(bufferIndex).bind();
		m_ibos.at(bufferIndex).setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_ibos.at(bufferIndex).allocate(m_meshes.at(bufferIndex)->getIndices().constData(), m_meshes.at(bufferIndex)->getIndices().size() * sizeof(GLushort));

		m_program->enableAttributeArray(0);
		m_program->enableAttributeArray(1);
		m_program->enableAttributeArray(2);
		//m_program->enableAttributeArray(3);

		m_vao.release();
		m_ibos.at(bufferIndex).release();
		m_vbos.at(bufferIndex).release();
	m_program->release();
}

void Graphics::updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex, int count)
{
	m_vbos.at(bufferIndex).bind();
	m_vbos.at(bufferIndex).write(offset * sizeof(Vertex), vertex, sizeof(Vertex) * count);
	m_vbos.at(bufferIndex).release();
}

void Graphics::updateVertexBufferData(int offset, const Vertex *vertex, int count, QOpenGLBuffer *buffer)
{
	buffer->bind();
	buffer->write(offset * sizeof(Vertex), vertex, sizeof(Vertex) *count);
	buffer->release();
}

void Graphics::updateVertexBufferData(int offset, const QVector<Vertex> &vertices, int bufferIndex)
{
	m_vbos.at(bufferIndex).bind();
	for (int i = 0; i < vertices.count(); ++i)
	{
		m_vbos.at(bufferIndex).write((offset + i) * sizeof(Vertex), vertices.constData(), sizeof(Vertex) * vertices.count());
	}
	m_vbos.at(bufferIndex).bind();
}

void Graphics::addMesh(std::shared_ptr<Mesh> mesh, QOpenGLBuffer::UsagePattern bufferUsage)
{
	m_meshes.append(mesh);
	m_drawState.push_back(true);
	initBuffer(m_meshes.count() - 1, bufferUsage);
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
		if (!m_drawState.at(i))
		{
			++i;
			continue;
		}
		auto bezier = std::static_pointer_cast<BezierCube>(*it);
		if (bezier)
		{
			m_program->setUniformValue(m_program->uniformLocation("isModel"), bezier->isModel());
		}
		m_program->setUniformValue(m_program->uniformLocation("model"), (*it)->getModelMatrix());
		m_program->setUniformValue(m_program->uniformLocation("MVP"), projView * (*it)->getModelMatrix());
		m_vao.bind();
		m_vbos.at(i).bind();
		m_ibos.at(i).bind();

		m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::getPositionOffset(), Vertex::PositionColorNormalTupleSize, Vertex::getStride());
		m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::getColorOffset(), Vertex::PositionColorNormalTupleSize, Vertex::getStride());
		m_program->setAttributeBuffer(2, GL_FLOAT, Vertex::getNormalOffset(), Vertex::PositionColorNormalTupleSize, Vertex::getStride());
		glDrawElements((*it)->getDrawMode(), (*it)->getIndices().size(), GL_UNSIGNED_SHORT, nullptr);
		m_ibos.at(i).release();
		m_vbos.at(i).release();
		m_vao.release();
		++i;
	}
	m_program->release();
}

void Graphics::setDrawState(bool draw, int index)
{
	m_drawState.at(index) = draw;
}

QOpenGLShaderProgram* Graphics::getProgram()
{
	return m_program;
}

void Graphics::updateJellyData(int jellyIndex, const std::vector<JellyPoint>& positions)
{
	std::dynamic_pointer_cast<JellyCube>(m_meshes.at(jellyIndex))->updateVerticesPositions(positions);
	updateVertexBufferData(0, m_meshes.at(jellyIndex)->getVertices(), jellyIndex);
}
