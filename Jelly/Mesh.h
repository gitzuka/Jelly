#pragma once
#include "Vertex.h"
#include <qvector.h>
#include <qopengl.h>

class Mesh
{
public:
	Mesh();
	//Mesh(const QVector<Vertex> &vertices, const QVector<int> &indices, const QVector<Vertex> &normals);
	Mesh(const std::vector<Vertex> &vertices, GLenum drawMode);
	explicit Mesh(GLenum drawMode);
	//Mesh(const Mesh &);
	virtual ~Mesh() = 0;
	virtual void generateVertices() = 0;
	//Mesh &Mesh::operator=(const Mesh&);

	//void createVertices(const QVector<Vertex> &vertices);
	//void initBuffer();
	//void updateBufferData(int offset, const Vertex *vertex);
	GLenum getDrawMode() const;
	//int getVerticesCount() const;
	const std::vector<Vertex>& getVertices() const;

	//const QVector<int>& getIndices() const;
	//const QVector<Vertex>& getNormals() const;
	//void draw();

protected:
	std::vector<Vertex> m_vertices;
	GLenum m_drawMode;

private:
	//QVector<int> m_indices;
	//QVector<Vertex> m_normals;
	//QOpenGLBuffer m_vertexBuffer;
	//QOpenGLVertexArrayObject m_vao;
	//QOpenGLShaderProgram *m_program;
};
