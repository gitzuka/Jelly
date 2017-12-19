#include "Renderer.h"
#include <iostream>
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
QVector4D light_position = { 00.0f, 00.0f, 100.0f, 1.0f };
QVector4D light_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
QVector4D light_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
QVector4D light_specular = { 1.0f, 1.0f, 1.0f, 1.0f };

QVector4D material_ambient = { 1.0f, 0.0f, 1.0f, 1.0f };
QVector4D material_diffuse = { 1.0f, 0.8f, 0.0f, 1.0f };
QVector4D material_specular = { 1.0f, 0.8f, 0.0f, 1.0f };
float  material_shininess = 20.0f;
QVector4D ambient_product;
QVector4D diffuse_product;
QVector4D specular_product;


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
		(*it)->initBuffer(m_program);
	}
	for (QVector<std::shared_ptr<Graphics>>::iterator it = m_axis.begin(); it != m_axis.end(); ++it)
	{
		(*it)->initBuffer(m_programAxis);
	}*/
}

//void Renderer::initShadersParameters()
//{
//	ambient_product = light_ambient * material_ambient;
//	diffuse_product = light_diffuse * material_diffuse;
//	specular_product = light_specular * material_specular;
//	m_program->bind();
//	m_program->setUniformValue(m_program->uniformLocation("Shininess"), material_shininess);
//	m_program->setUniformValue(m_program->uniformLocation("AmbientProduct"), ambient_product);
//	m_program->setUniformValue(m_program->uniformLocation("DiffuseProduct"), diffuse_product);
//	m_program->setUniformValue(m_program->uniformLocation("SpecularProduct"), specular_product);
//	m_program->setUniformValue(m_program->uniformLocation("LightPosition"), light_position);
//	m_program->release();
//}

void Renderer::addGraphicComponent(std::shared_ptr<Graphics> graphics)
{
	m_graphics.append(graphics);
}


void Renderer::draw()
{
	/*m_program->bind();


	QMatrix4x4 mvp = m_camera.m_projectionMatrix  * m_camera.m_viewMatrix;
	for (QVector<std::shared_ptr<Graphics>>::iterator it = m_graphics.begin(); it != m_graphics.end(); ++it)
	{
		(*it)->setModelMatrix((*it)->getModelMatrix() * Camera::createRotationY(Camera::convertToRadians(0.1f)));
		m_program->setUniformValue(m_program->uniformLocation("MVP"), mvp * (*it)->getModelMatrix());
		(*it)->getVao()->bind();
		glDrawArrays((*it)->getDrawMode(), 0, (*it)->getMesh().getVertices().count());
		(*it)->getVao()->release();
	}

	m_program->release();
	drawAxis();*/
}

Camera& Renderer::getCamera()
{
	return m_camera;
}
