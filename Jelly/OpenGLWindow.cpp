#include "OpenGLWindow.h"
#include <QtGui>

OpenGLWindow::OpenGLWindow(QWidget* parent) : m_renderer(nullptr)
{
}

OpenGLWindow::~OpenGLWindow()
{
	makeCurrent();
}

void OpenGLWindow::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
}

void OpenGLWindow::initializeGL()
{
	this->setCursor(Qt::BlankCursor);
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	QOpenGLShaderProgram *program = new QOpenGLShaderProgram();
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.vert");
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.frag");
	program->link();

	std::shared_ptr<Graphics> lineGraphics = std::make_shared<Graphics>(program);

	m_renderer->addGraphicComponent(lineGraphics);
	emit initializedGL();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	emit paintedGL();
	//m_renderer->draw();
}

void OpenGLWindow::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	m_renderer->getCamera().m_projectionMatrix = Camera::createProjection(width, height);
	m_renderer->getCamera().m_projView = m_renderer->getCamera().m_projectionMatrix * m_renderer->getCamera().m_viewMatrix;
}

void OpenGLWindow::mousePressEvent(QMouseEvent* event)
{
	m_renderer->getCamera().m_mousePos = event->pos();
	//m_renderer->getCamera().m_mousePos.setX(event->pos().x() - this->width() / 2.0f);
	if (event->buttons() & Qt::LeftButton)
	{
		emit leftMouseClicked(event->x(), event->y(), QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier), this->width(), this->height(), true);
	}
	this->update();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
	//float x = event->x() - this->width() / 2.0f;
	float dx = event->x() - m_renderer->getCamera().m_mousePos.x();
	float dy = event->y() - m_renderer->getCamera().m_mousePos.y();
	if (event->buttons() & Qt::RightButton)
	{
		m_renderer->getCamera().mouseMoved(dx, dy);
	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		emit initRotation(dy, dx);
	}
	emit leftMouseClicked(event->x(), event->y(), QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier), this->width(), this->height(), false);

	m_renderer->getCamera().m_mousePos = event->pos();
	//this->update();
	//float x = event->x() - this->width() / 2.0f;
	//float dx = x - m_renderer->getCamera().m_mousePos.x();
	//float dy = event->y() - m_renderer->getCamera().m_mousePos.y();
	//if (event->buttons() & Qt::RightButton)
	//{
	//	m_renderer->getCamera().mouseMoved(dx + this->width() / 2.0f, dy);
	//}
	//emit leftMouseClicked(dx, dy, QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier), this->width(), this->height(), false);

	////m_renderer->getCamera().m_mousePos = event->pos();
	//m_renderer->getCamera().m_mousePos.setX(x);
	////this->update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *event)
{
	m_renderer->getCamera().keyPressed(event->key());
	/*emit keyPressed(event);
	switch (event->key())
	{
	case 'T':
	{
		emit initRotation(0, 45.0f);
		break;
	}
	}*/
	this->update();
}

void OpenGLWindow::setCursorState(bool checked)
{
	checked ? this->setCursor(Qt::BlankCursor) : this->setCursor(Qt::ArrowCursor);
}
