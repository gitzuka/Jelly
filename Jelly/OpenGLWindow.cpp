#include "OpenGLWindow.h"
#include "JellyCube.h"
#include "CubeFrame.h"
#include <QtGui>

OpenGLWindow::OpenGLWindow(QWidget* parent)
{
	//std::shared_ptr<Mesh> cube = std::make_shared<JellyCube>(JellyCube(GL_LINE, QVector3D(0, 0, 1), 1.0f)) ;
}

OpenGLWindow::~OpenGLWindow()
{
	makeCurrent();
}

void OpenGLWindow::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);

	QOpenGLShaderProgram *program = new QOpenGLShaderProgram();
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.vert");
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.frag");
	program->link();

	std::shared_ptr<Graphics> lineGraphics = std::make_shared<Graphics>(program);
	lineGraphics->addMesh(std::make_shared<CubeFrame>(GL_LINES, QVector3D(1.0f, 0, 0), 1.0f));
	lineGraphics->addMesh(std::make_shared<JellyCube>(GL_LINES, QVector3D(0, 1.0f, 1.0f), 1.0f));

	m_renderer.addGraphicComponent(lineGraphics);
	m_renderer.initBuffers();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_renderer.draw();
}

void OpenGLWindow::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	m_renderer.getCamera().m_projectionMatrix = Camera::createProjection(width, height);
	m_renderer.getCamera().m_projView = m_renderer.getCamera().m_projectionMatrix * m_renderer.getCamera().m_viewMatrix;
}

void OpenGLWindow::mousePressEvent(QMouseEvent* event)
{
	m_renderer.getCamera().m_mousePos = event->pos();
	this->update();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
	float dx = event->x() - m_renderer.getCamera().m_mousePos.x();
	float dy = event->y() - m_renderer.getCamera().m_mousePos.y();
	if (event->buttons() & Qt::LeftButton)
	{
	}
	else if (event->buttons() & Qt::RightButton)
	{
		m_renderer.getCamera().mouseMoved(dx, dy);
	}
	m_renderer.getCamera().m_mousePos = event->pos();
	this->update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent* event)
{
	m_renderer.getCamera().keyPressed(event->key());
	this->update();
}
