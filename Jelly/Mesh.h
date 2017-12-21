#pragma once
#include "Vertex.h"
#include <qvector.h>
#include <qopengl.h>
#include <QMatrix4x4>

class Mesh
{
public:
	Mesh();
	Mesh(const QVector<Vertex> &vertices, GLenum drawMode);
	explicit Mesh(GLenum drawMode);
	virtual ~Mesh() = 0;

	virtual void generateVertices() = 0;
	virtual void generateIndices() = 0;

	GLenum getDrawMode() const;
	const QVector<Vertex>& getVertices() const;
	const QVector<GLushort>& getIndices() const;
	const QMatrix4x4& getModelMatrix() const;
	void setModelMatrix(const QMatrix4x4 &mat);

protected:
	QVector<Vertex> m_vertices;
	QVector<GLushort> m_indices;
	QMatrix4x4 m_modelMatrix;
	GLenum m_drawMode;

private:
	//QVector<int> m_indices;
	//QVector<Vertex> m_normals;
	//QOpenGLBuffer m_vertexBuffer;
	//QOpenGLVertexArrayObject m_vao;
	//QOpenGLShaderProgram *m_program;
};
