#include "OpenGLWindow.h"
#include "JellyCube.h"

OpenGLWindow::OpenGLWindow(QWidget* parent)
{
	std::shared_ptr<Mesh> cube = std::make_shared<JellyCube>(JellyCube(GL_LINE, QVector3D(0, 0, 1), 1.0f)) ;
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::initializeGL()
{
}

void OpenGLWindow::paintGL()
{
}

void OpenGLWindow::resizeGL(int width, int height)
{
}

void OpenGLWindow::destroyGL()
{
}
