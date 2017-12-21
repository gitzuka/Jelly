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
	explicit Graphics(QOpenGLShaderProgram *program);
	~Graphics();

	//Graphics(const Graphics&);
	//Graphics &Graphics::operator=(const Graphics&);

	void initBuffer();
	void updateVertexBufferData(int offset, const Vertex *vertex, int bufferIndex);
	void addMesh(const std::shared_ptr<Mesh> mesh);
	void assignShaderProgram(QOpenGLShaderProgram *program);
	const QVector<std::shared_ptr<Mesh>>& Graphics::getMeshes() const;
	void draw(const QMatrix4x4 &projView);

private:
	QVector<std::shared_ptr<Mesh>> m_meshes;
	std::vector<QOpenGLBuffer> m_vbos;
	std::vector<QOpenGLBuffer> m_ibos;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLShaderProgram *m_program;
};
