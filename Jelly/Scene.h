#pragma once
#include "Renderer.h"
#include "Jelly.h"

class Scene : public QObject
{
	Q_OBJECT
public:
	Scene();
	~Scene();

	Renderer *getRenderer();
	Jelly& getJelly();

private:
	Renderer m_renderer;
	Jelly m_jelly;
	int m_jellyIndex;
	int m_frameIndex;
	int m_cursorIndex;
	int m_bezierIndex;
	int m_cuboidIndex;
	int m_modelIndex;
	bool m_drawPoints;
	QMatrix4x4 m_local;

signals:
	void frameMoved(std::shared_ptr<CubeFrame> cubeFrame);
	void cursorPosUpdated(const QVector3D &pos);

private slots:
	void initializeScene();
	void draw();
	void moveFrame(float x, float y, bool z, float width, float height, bool mouseClicked);
	void setCursorDrawState(int draw);
	void updatePointsModelMats();
	void setPointsDrawState(int draw);
	void setFrameDrawState(int draw);
	void setJellyDrawState(int draw);
	void setBezierDrawState(int draw);
	void setCuboidDrawState(int draw);
	void setModelDrawState(int draw);
	void rotateFrame(float pitch, float yaw);
	//void setDrawState(bool draw, )
};
