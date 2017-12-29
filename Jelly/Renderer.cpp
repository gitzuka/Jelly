#include "Renderer.h"
#include <qmath.h>

//struct LightInfo
//{
//	QVector3D Position;	//Light Position in eye-coords
//	QVector3D La;		//Ambient light intensity
//	QVector3D Ld;		//Diffuse light intensity
//	QVector3D Ls;		//Specular light intensity
//};
//
//struct MaterialInfo
//{
//	QVector3D Ka;			//Ambient reflectivity
//	QVector3D Kd;			//Diffuse reflectivity
//	QVector3D Ks;			//Specular reflectivity
//	float Shininess;	//Specular shininess factor
//};

//QVector4D light_position = { 100.0f, 100.0f, 100.0f, 1.0f };
//QVector4D light_position = { 00.0f, 00.0f, 100.0f, 1.0f };
//QVector4D light_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
//QVector4D light_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
//QVector4D light_specular = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//QVector4D material_ambient = { 1.0f, 0.0f, 1.0f, 1.0f };
//QVector4D material_diffuse = { 1.0f, 0.8f, 0.0f, 1.0f };
//QVector4D material_specular = { 1.0f, 0.8f, 0.0f, 1.0f };
//float  material_shininess = 20.0f;
//QVector4D ambient_product;
//QVector4D diffuse_product;
//QVector4D specular_product;


Renderer::Renderer() : m_camera(Camera())
{
}

Renderer::~Renderer()
{
}

void Renderer::initBuffers()
{
	/*for (QVector<std::shared_ptr<Graphics>>::iterator it = m_graphics.begin(); it != m_graphics.end(); ++it)
	{
		(*it)->initBuffer();
	}*/
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
