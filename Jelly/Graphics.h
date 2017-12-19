#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "Vertex.h"
#include "Mesh.h"

class Graphics
{
public:
	Graphics(const QVector<Mesh> &meshes);
	Graphics();
	~Graphics();

	void initBuffer(QOpenGLShaderProgram *program);
	void updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex);
	void addMesh(const Mesh &mesh);
	QOpenGLVertexArrayObject* getVao();
	const std::vector<Mesh>& Graphics::getMeshes() const;

private:
	std::vector<Mesh> m_meshes;
	std::vector<QOpenGLBuffer> m_vertexBuffers;
	QOpenGLVertexArrayObject m_vao;
};
