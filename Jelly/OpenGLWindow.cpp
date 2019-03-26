#include "OpenGLWindow.h"
#include <QtGui>
#include "Cursor3D.h"

OpenGLWindow::OpenGLWindow(QWidget* parent) : m_renderer(nullptr), m_dx(0), m_dy(0)
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
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/vs2015/Projects/Jelly/Jelly/linesObject.vert");
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/vs2015/Projects/Jelly/Jelly/linesObject.frag");
	program->link();

	std::shared_ptr<Graphics> lineGraphics = std::make_shared<Graphics>(program);

	m_renderer->addGraphicComponent(lineGraphics);

	QOpenGLShaderProgram *programBezier = new QOpenGLShaderProgram();
	programBezier->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/vs2015/Projects/Jelly/Jelly/bezierObject.vert");
	programBezier->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/vs2015/Projects/Jelly/Jelly/bezierObject.frag");
	programBezier->link();

	std::shared_ptr<Graphics> bezierGraphics = std::make_shared<Graphics>(programBezier);
	m_renderer->addGraphicComponent(bezierGraphics);

	emit initializedGL();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	emit paintedGL();
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
	if (event->buttons() & Qt::LeftButton)
	{
		emit leftMouseClicked(event->x(), event->y(), QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier), this->width(), this->height(), true);
	}
	this->update();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
	float dx = event->x() - m_renderer->getCamera().m_mousePos.x();
	float dy = event->y() - m_renderer->getCamera().m_mousePos.y();
	m_renderer->getCamera().m_mousePos = event->pos();
	if (event->buttons() & Qt::RightButton)
	{
		m_renderer->getCamera().mouseMoved(dx, dy);
	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		emit initRotation(dy, dx);
	}
	if (this->cursor().shape() == Qt::ArrowCursor)
	{
		return;
	}
	emit leftMouseClicked(event->x(), event->y(), QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier), this->width(), this->height(), false);
}

void OpenGLWindow::keyPressEvent(QKeyEvent *event)
{
	m_renderer->getCamera().keyPressed(event->key());
	emit keyPressed(event);
	this->update();
}

void OpenGLWindow::setCursorState(int checked)
{
	checked ? this->setCursor(Qt::BlankCursor) : this->setCursor(Qt::ArrowCursor);
}
