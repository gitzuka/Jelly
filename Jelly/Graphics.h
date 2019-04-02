#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "Vertex.h"
#include "Mesh.h"
#include <memory>

class JellyPoint;
class Graphics : public QObject
{
	Q_OBJECT
public:
	explicit Graphics(QOpenGLShaderProgram *program);
	virtual ~Graphics();

	void initBuffers();
	void initBuffer(QOpenGLBuffer *vertBuffer, QOpenGLBuffer *indexBuffer, QOpenGLBuffer::UsagePattern bufferUsage, std::shared_ptr<Mesh> mesh);
	void initBuffer(int bufferIndex, QOpenGLBuffer::UsagePattern bufferUsage);
	void updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex, int count);
	void updateVertexBufferData(int offset, const Vertex *vertex, int count, QOpenGLBuffer *buffer);
	void updateVertexBufferData(int offset, const QVector<Vertex> &vertices, int bufferIndex);
	void addMesh(std::shared_ptr<Mesh> mesh, QOpenGLBuffer::UsagePattern bufferUsage);
	void assignShaderProgram(QOpenGLShaderProgram *program);
	const QVector<std::shared_ptr<Mesh>>& getMeshes() const;
	void draw(const QMatrix4x4 &projView);
	void setDrawState(bool draw, int index);
	QOpenGLShaderProgram* getProgram();

private:
	QVector<std::shared_ptr<Mesh>> m_meshes;
	std::vector<bool> m_drawState;
	std::vector<QOpenGLBuffer> m_vbos;
	std::vector<QOpenGLBuffer> m_ibos;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLShaderProgram *m_program;

public slots:
	void updateJellyData(int jellyIndex, const std::vector<JellyPoint>& positions);
};
