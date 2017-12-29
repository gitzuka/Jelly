#include "Scene.h"

Scene::Scene()
{
	//initializeScene();
}

Scene::~Scene()
{
}

void Scene::connect()
{
	//connect(&m_jelly, SIGNAL(simulationUpdated(int)), &m_renderer.)
}

void Scene::initializeScene()
{
	/*QOpenGLShaderProgram *program = new QOpenGLShaderProgram();
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.vert");
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/Jelly/Jelly/linesObject.frag");
	program->link();

	std::shared_ptr<Graphics> lineGraphics = std::make_shared<Graphics>(program);
	lineGraphics->addMesh(std::make_shared<JellyCube>(GL_LINES, lineGraphics->getMeshes().count(), QVector3D(0, 1.0f, 1.0f), 1.0f));
	lineGraphics->addMesh(std::make_shared<CubeFrame>(GL_LINES, lineGraphics->getMeshes().count(), QVector3D(1.0f, 0, 0), 1.0f));
	m_renderer.addGraphicComponent(lineGraphics);*/
	std::shared_ptr<JellyCube> jellyCube = std::make_shared<JellyCube>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(0, 1.0f, 1.0f), 1.0f);
	std::shared_ptr<CubeFrame> cubeFrame = std::make_shared<CubeFrame>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(1.0f, 0, 0), 1.0f);
	m_jelly.createSpringsAndPoints(jellyCube, cubeFrame);
	//m_renderer.getGraphics(0)->addMesh(std::make_shared<JellyCube>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(0, 1.0f, 1.0f), 1.0f));
	m_renderer.getGraphics(0)->addMesh(jellyCube, QOpenGLBuffer::DynamicDraw);
	//m_renderer.getGraphics(0)->addMesh(std::make_shared<CubeFrame>(GL_LINES, m_renderer.getGraphics(0)->getMeshes().count(), QVector3D(1.0f, 0, 0), 1.0f), QOpenGLBuffer::StaticDraw);
	m_renderer.getGraphics(0)->addMesh(cubeFrame, QOpenGLBuffer::StaticDraw);
	//m_jelly.startSimulation();
}

void Scene::draw()
{
	//std::dynamic_pointer_cast<JellyCube>(m_renderer.getGraphics(0))->updateVerticesPositions(m_jelly.getJellyPoints());
	m_renderer.getGraphics(0)->updateJellyData(0, m_jelly.getJellyPoints());
	m_renderer.draw();
}

Renderer *Scene::getRenderer()
{
	return &m_renderer;
}

Jelly &Scene::getJelly()
{
	return m_jelly;
}
