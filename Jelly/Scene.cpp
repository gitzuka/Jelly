#include "Scene.h"
#include "Cursor3D.h"
#include "Point3D.h"
#include "BezierCube.h"
#include "ModelLoader.h"
#include "Cuboid.h"

Scene::Scene() : m_jellyIndex(-1), m_frameIndex(-1), m_cursorIndex(-1), m_bezierIndex(-1), m_cuboidIndex(-1), m_modelIndex(-1), m_drawPoints(true)
{
}

Scene::~Scene()
{
}

void Scene::loadModel()
{
	ModelLoader model;

	if (!model.Load("C:/Users/Andrzej/Documents/vs2015/Projects/Jelly/Jelly/Resources/WusonOBJ.obj", ModelLoader::PathType::AbsolutePath))
	{
		return;
	}
	QVector<float> *vertices;

	QVector<float> *normals;
	QVector<unsigned int> *indices;

	model.getBufferData(&vertices, &normals, &indices);
	QVector<QVector3D> positions;
	positions.reserve(vertices->count() / 3);
	for (int i = 0; i < vertices->count(); i += 3)
	{
		positions.push_back(QVector3D((vertices->at(i)) * 0.3f + 0.5f, (vertices->at(i + 1)) * 0.3f + 0.3f, (vertices->at(i + 2))* 0.3f + 0.5f));
	}
	QVector<QVector3D> vecnormals;
	vecnormals.reserve(normals->count() / 3);
	for (int i = 0; i < normals->count(); i += 3)
	{
		vecnormals.push_back(QVector3D(normals->at(i), normals->at(i + 1), normals->at(i + 2)));
	}
	QVector<GLushort> vecindices;
	vecindices.reserve(indices->count());
	for (int i = 0; i < indices->count(); ++i)
	{
		vecindices.push_back(indices->at(i));
	}
	QVector<Vertex> vertexes;
	vertexes.reserve(positions.count());
	for (int i = 0; i < positions.count(); ++i)
	{
		vertexes.push_back(Vertex(positions.at(i), QVector3D(1, 0, 1), vecnormals.at(i)));
	}
	std::shared_ptr<BezierCube> bezierModel = std::make_shared<BezierCube>(vertexes, vecindices, GL_TRIANGLES, m_renderer.getGraphics(1)->getMeshes().count(), QVector3D(1, 0, 1), true);
	m_renderer.getGraphics(1)->addMesh(bezierModel, QOpenGLBuffer::StaticDraw);
	m_modelIndex = m_renderer.getGraphics(1)->getMeshes().count() - 1;
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
	float size = 8.0f;
	std::shared_ptr<Cuboid> cuboid = std::make_shared<Cuboid>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), size);
	m_renderer.getGraphics(0)->addMesh(cuboid, QOpenGLBuffer::StaticDraw);
	m_cuboidIndex = m_renderer.getGraphics(0)->getMeshes().count() - 1;
		
	m_jelly.setBoundingX(cuboid->getBoundingX());
	m_jelly.setBoundingY(cuboid->getBoundingY());
	m_jelly.setBoundingZ(cuboid->getBoundingZ());

	m_startPoinsIndex = m_cuboidIndex + 1;
	for (std::vector<JellyPoint>::const_iterator it = m_jelly.getJellyPoints().begin(); it != m_jelly.getJellyPoints().end(); ++it)
	{
		m_renderer.getGraphics(0)->addMesh(std::make_shared<Point3D>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count()), QOpenGLBuffer::StaticDraw);
		m_renderer.getGraphics(0)->getMeshes().at(m_renderer.getGraphics(0)->getMeshes().count() - 1)->setModelMatrix(Camera::createTranslation(it->getPosition()));
	}

	int div = 32;
	std::shared_ptr<BezierCube> bezierCube = std::make_shared<BezierCube>(GL_TRIANGLES, m_renderer.getGraphics(1)->getMeshes().count(), div, QVector3D(1, 0, 1), false);
	m_renderer.getGraphics(1)->addMesh(bezierCube, QOpenGLBuffer::StaticDraw);
	m_bezierIndex = m_renderer.getGraphics(1)->getMeshes().count() - 1;
	m_renderer.getGraphics(1)->setDrawState(false, m_bezierIndex);

	loadModel();
	QOpenGLShaderProgram *program = m_renderer.getGraphics(1)->getProgram();
	program->bind();
	program->setUniformValue("lightPos", QVector3D(0.0f, -10.0f, 0.0f));
	program->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
	program->setUniformValue("objectColor", QVector3D(1.0f, 0.0f, 1.0f));
	program->setUniformValue("light.intensity", QVector3D(0.1f, 1.0f, 1.0f));
	program->setUniformValue("material.Ka", QVector3D(0.05f, 0.2f, 0.05f));
	program->setUniformValue("materialKd", QVector3D(0.3f, 0.5f, 0.3f));
	program->setUniformValue("materialKs", QVector3D(0.6f, 0.6f, 0.6f));
	program->setUniformValue("materialShininess", 50.f);
	program->release();
}

void Scene::draw()
{
	QOpenGLShaderProgram *program = m_renderer.getGraphics(1)->getProgram();
	program->bind();
	program->setUniformValueArray(program->uniformLocation("points"), m_jelly.getJellyPointsPositions().constData(), m_jelly.getJellyPointsPositions().size());
	program->setUniformValueArray(program->uniformLocation("pointsNormals"), m_jelly.getJellyPointsPositionsNormals().constData(), m_jelly.getJellyPointsPositionsNormals().size());
	program->setUniformValue(program->uniformLocation("view"), m_renderer.getCamera().m_viewMatrix);
	program->setUniformValue(program->uniformLocation("rotation"), m_rotationMat);
	program->setUniformValue(program->uniformLocation("eyePos"), m_renderer.getCamera().m_eyeVector);
	program->release();
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
		std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex))->moveFrame(m_renderer.getGraphics(0)->getMeshes().at(m_cursorIndex)->getModelMatrix(), m_renderer.getCamera());
		emit frameMoved(std::dynamic_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex)));
	}
	emit cursorPosUpdated(pos);
}



void Scene::setCursorDrawState(int draw)
{
	m_renderer.getGraphics(0)->setDrawState(draw, m_cursorIndex);
}

void Scene::updatePointsModelMats()
{
	int i = m_startPoinsIndex;
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
	for (int i = m_startPoinsIndex; i < m_renderer.getGraphics(0)->getMeshes().count(); ++i)
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

void Scene::setBezierDrawState(int draw)
{
	m_renderer.getGraphics(1)->setDrawState(draw, m_bezierIndex);
}

void Scene::setCuboidDrawState(int draw)
{
	m_renderer.getGraphics(0)->setDrawState(draw, m_cuboidIndex);
}

void Scene::setModelDrawState(int draw)
{
	m_renderer.getGraphics(1)->setDrawState(draw, m_modelIndex);
}

void Scene::rotateFrame(float pitch, float yaw)
{
	float rotationFactor = 1;
	auto frame = std::static_pointer_cast<CubeFrame>(m_renderer.getGraphics(0)->getMeshes().at(m_frameIndex));
	frame->rotate(rotationFactor * pitch, rotationFactor * yaw, m_renderer.getCamera());
	m_rotationMat = frame->getRotationmat();
	emit frameMoved(frame);
}

Renderer* Scene::getRenderer()
{
	return &m_renderer;
}

Jelly& Scene::getJelly()
{
	return m_jelly;
}
