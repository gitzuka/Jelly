#pragma once
#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QDateTime>
#include "Renderer.h"

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
public:
	explicit OpenGLWindow(QWidget *parent = 0);
	~OpenGLWindow();
	//Physics m_physicComponent;

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void destroyGL();

	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);
	//void keyPressEvent(QKeyEvent  *event);

private:
	//	QOpenGLShaderProgram *m_program, *m_axisProgam;
	//	int m_frameCount;
	//	QTime m_frameTime;
	//	Renderer m_renderer;
	//
	//	QVector<Vertex> createCube();
	//	QVector<Vertex> createAxeX();
	//	QVector<Vertex> createAxeY();
	//	QVector<Vertex> createAxeZ();
	//	//void calculateNormals(const QVector<Vertex> &vertices, const QVector<int> &indices);
	//	public slots:
	//	void rotateCube(QQuaternion q);
	//
	//signals:
	//	//void mousePressed(QMouseEvent *event);
	//	//void mouseMoved(QMouseEvent *event);
	//	//void keyPressed(QKeyEvent *event);
	//	void paintedGL();
	//	void initializedGL(QOpenGLShaderProgram*);
	//	void fpsUpdated(float);
};

#endif //GLANIMATIONWINDOW_H