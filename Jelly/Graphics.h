#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "Vertex.h"
#include "Mesh.h"
#include <memory>

class Graphics
{
public:
	Graphics(const QVector<std::shared_ptr<Mesh>> &meshes);
	Graphics();
	~Graphics();

	void initBuffer(QOpenGLShaderProgram *program);
	void updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex);
	void addMesh(const std::shared_ptr<Mesh> mesh);
	QOpenGLVertexArrayObject* getVao();
	const QVector<std::shared_ptr<Mesh>>& Graphics::getMeshes() const;

private:
	QVector<std::shared_ptr<Mesh>> m_meshes;
	std::vector<QOpenGLBuffer> m_vertexBuffers;
	QOpenGLVertexArrayObject m_vao;
};
