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

	void setRenderer(Renderer *renderer);
	//Physics m_physicComponent;

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	Renderer *m_renderer;
	float m_dx;
	float m_dy;

private slots:
	void setCursorState(int checked);

signals:
	void initializedGL();
	void paintedGL();
	void leftMouseClicked(float x, float y, bool z, float width, float height, bool clicked);
	void keyPressed(QKeyEvent *event);
	void initRotation(float, float);
};

#endif //GLANIMATIONWINDOW_H