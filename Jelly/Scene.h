#pragma once
#include "Renderer.h"
#include "Jelly.h"

class Scene : public QObject
{
	Q_OBJECT
public:
	Scene();
	~Scene();

	void connect();
	Renderer *getRenderer();
	Jelly& getJelly();
	//void initializeScene();
private:
	Renderer m_renderer;
	Jelly m_jelly;
	

public slots:
	void initializeScene();
	void draw();
};
