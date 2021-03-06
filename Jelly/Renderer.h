#pragma once
#include "Graphics.h"
#include <memory>
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void addGraphicComponent(std::shared_ptr<Graphics> graphics);
	std::shared_ptr<Graphics> getGraphics(int index);
	void draw();
	//void draw(Camera &camera);
	Camera& getCamera();

private:
	QVector<std::shared_ptr<Graphics>> m_graphics;
	Camera m_camera;
};
