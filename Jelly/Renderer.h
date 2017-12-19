#pragma once
#include "Graphics.h"
#include <memory>
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	//Renderer(QOpenGLShaderProgram *program);
	~Renderer();


	void initBuffers();
	//void initShadersParameters();
	void addGraphicComponent(std::shared_ptr<Graphics>);
	void draw();
	Camera& getCamera();

private:
	QVector<std::shared_ptr<Graphics>> m_graphics;
	//QVector<QOpenGLBuffer> m_vertexBuffers;
	//QVector<QOpenGLBuffer> m_indexBuffers;
	//QVector<GLenum> m_drawModes;
	//GLenum m_drawMode;
	//QVector<QOpenGLVertexArrayObject> m_vaos;
	//QOpenGLShaderProgram *m_program;
	Camera m_camera;
};
