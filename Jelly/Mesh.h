#pragma once
#include "Vertex.h"
#include <qvector.h>
#include <qopengl.h>
#include <QMatrix4x4>

class Mesh
{
public:
	Mesh();
	//Mesh(const QVector<Vertex> &vertices, const QVector<int> &indices, const QVector<Vertex> &normals);
	Mesh(const QVector<Vertex> &vertices, GLenum drawMode);
	explicit Mesh(GLenum drawMode);
	//Mesh(const Mesh &);
	virtual ~Mesh() = 0;

	virtual void generateVertices() = 0;
	virtual void generateIndices() = 0;
	//Mesh &Mesh::operator=(const Mesh&);

	//void createVertices(const QVector<Vertex> &vertices);
	//void initBuffer();
	//void updateBufferData(int offset, const Vertex *vertex);
	GLenum getDrawMode() const;
	//int getVerticesCount() const;
	const QVector<Vertex>& getVertices() const;
	const QVector<GLushort>& getIndices() const;
	const QMatrix4x4& getModelMatrix() const;
	//const QVector<int>& getIndices() const;
	//const QVector<Vertex>& getNormals() const;
	//void draw();

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
