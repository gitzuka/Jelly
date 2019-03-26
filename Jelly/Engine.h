#pragma once
#include <qtimer.h>


class Engine
{
public:
	Engine(int updateFrequency, int renderFrequency);
	~Engine();

	//void Start();
	//void Pause();

private:
	QTimer m_timerUpdate;
	QTimer m_timerRender;
	int m_updateFrequency;
	int m_renderFrequency;

	//void Update();
	//void Render();
};