#include "Renderer.h"
#include <qmath.h>

Renderer::Renderer() : m_camera(Camera())
{
}

Renderer::~Renderer()
{
}

void Renderer::addGraphicComponent(std::shared_ptr<Graphics> graphics)
{
	m_graphics.append(graphics);
}

std::shared_ptr<Graphics> Renderer::getGraphics(int index)
{
	return m_graphics.at(index);
}

void Renderer::draw()
{
	for (QVector<std::shared_ptr<Graphics>>::iterator it = m_graphics.begin(); it != m_graphics.end(); ++it)
	{
		(*it)->draw(m_camera.m_projView);
	}
}

Camera& Renderer::getCamera()
{
	return m_camera;
}
