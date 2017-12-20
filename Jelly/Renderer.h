#pragma once
#include "Graphics.h"
#include <memory>
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void initBuffers();
	void addGraphicComponent(const std::shared_ptr<Graphics> graphics);
	void draw();
	Camera& getCamera();

private:
	QVector<std::shared_ptr<Graphics>> m_graphics;
	Camera m_camera;
};
