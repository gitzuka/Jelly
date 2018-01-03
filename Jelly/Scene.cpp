#include "Scene.h"
#include "Cursor3D.h"
#include "Point3D.h"

Scene::Scene() : m_jellyIndex(-1), m_frameIndex(-1), m_cursorIndex(-1), m_drawPoints(true)
{
}

Scene::~Scene()
{
}

void Scene::initializeScene()
{
	std::shared_ptr<JellyCube> jellyCube = std::make_shared<JellyCube>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(0, 1.0f, 1.0f), 1.0f);
	std::shared_ptr<CubeFrame> cubeFrame = std::make_shared<CubeFrame>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(1.0f, 0, 0), 1.0f);
	m_jelly.createSpringsAndPoints(jellyCube, cubeFrame);
	m_renderer.getGraphics(0)->addMesh(jellyCube, QOpenGLBuffer::DynamicDraw);
	m_jellyIndex = m_renderer.getGraphics(0)->getMeshes().count() - 1;
	m_renderer.getGraphics(0)->addMesh(cubeFrame, QOpenGLBuffer::StaticDraw);
	m_frameIndex = m_renderer.getGraphics(0)->getMeshes().count() - 1;
	std::shared_ptr<Cursor3D> cursor3D = std::make_shared<Cursor3D>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count());
	m_renderer.getGraphics(0)->addMesh(cursor3D, QOpenGLBuffer::StaticDraw);
	m_cursorIndex = m_renderer.getGraphics(0)->getMeshes().count() - 1;

	for (std::vector<JellyPoint>::const_iterator it = m_jelly.getJellyPoints().begin(); it != m_jelly.getJellyPoints().end(); ++it)
	{
		QVector3D position = it->getPosition();
		m_renderer.getGraphics(0)->addMesh(std::make_shared<Point3D>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count()), QOpenGLBuffer::StaticDraw);
		m_renderer.getGraphics(0)->getMeshes().at(m_renderer.getGraphics(0)->getMeshes().count() - 1)->setModelMatrix(Camera::createTranslation(position));
	}
}

void Scene::draw()
{
	m_renderer.getGraphics(0)->updateJellyData(m_jellyIndex, m_jelly.getJellyPoints());
	if (m_drawPoints)
	{
		updatePointsModelMats();
	}
	m_renderer.draw();
}

void Scene::moveFrame(float x, float y, bool z, float width, float height, bool mouseClicked)
{
	QVector3D pos = std::dynamic_pointer_cast<Cursor3D>(m_renderer.getGraphics(0)->getMeshes().at(m_cursorIndex))->setPosition(x, y, z, width, height,
		m_renderer.getCamera());
	if (mouseClicked)
	{
		std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex))->moveFrame(m_renderer.getGraphics(0)->getMeshes().at(m_cursorIndex)->getModelMatrix());
		//m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex)->setModelMatrix(m_renderer.getGraphics(0)->getMeshes().at(m_cursorIndex)->getModelMatrix());
		emit frameMoved(std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex)));
	}
	//emit cursorPosUpdated(std::dynamic_pointer_cast<Cursor3D>(m_renderer.getGraphics(0)->getMeshes().at(m_cursorIndex))->getPosition());
	emit cursorPosUpdated(pos);
}



void Scene::setCursorDrawState(int draw)
{
	m_renderer.getGraphics(0)->setDrawState(draw, m_cursorIndex);
}

void Scene::updatePointsModelMats()
{
	int i = 3;
	for (std::vector<JellyPoint>::const_iterator it = m_jelly.getJellyPoints().begin(); it != m_jelly.getJellyPoints().end(); ++it)
	{
		QVector3D position = it->getPosition();
		m_renderer.getGraphics(0)->getMeshes().at(i)->setModelMatrix(Camera::createTranslation(position));
		++i;
	}
}

void Scene::setPointsDrawState(int draw)
{
	m_drawPoints = draw;
	for (int i = 3; i < m_renderer.getGraphics(0)->getMeshes().count(); ++i)
	{
		m_renderer.getGraphics(0)->setDrawState(draw, i);
	}
}

void Scene::setFrameDrawState(int draw)
{
	m_renderer.getGraphics(0)->setDrawState(draw, m_frameIndex);
}

void Scene::setJellyDrawState(int draw)
{
	m_renderer.getGraphics(0)->setDrawState(draw, m_jellyIndex);
}

void Scene::rotateFrame(float pitch, float yaw)
{
	std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex))->rotate(pitch, yaw);
	emit frameMoved(std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex)));
}

Renderer* Scene::getRenderer()
{
	return &m_renderer;
}

Jelly& Scene::getJelly()
{
	return m_jelly;
}
