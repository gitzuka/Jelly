#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connectUi();
	m_scene.getJelly().startSimulation();
}

MainWindow::~MainWindow()
{

}

void MainWindow::connectUi()
{
	connect(ui.doubleSpinBox_c1, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setc1(double)));
	connect(ui.doubleSpinBox_k, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setk(double)));
	connect(ui.doubleSpinBox_mass, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setMasses(double)));
	connect(ui.pushButton_random, SIGNAL(clicked()), &m_scene.getJelly(), SLOT(randomVelocities()));
	connect(ui.openGLWidget, SIGNAL(initializedGL()), &m_scene, SLOT(initializeScene()));
	connect(ui.openGLWidget, SIGNAL(paintedGL()), &m_scene, SLOT(draw()));
	connect(&m_scene.getJelly(), SIGNAL(simulationUpdated(int)), &m_scene, SLOT(draw(int)));
	connect(m_scene.getJelly().getPhysicsTimer(), SIGNAL(timeout()), &m_scene.getJelly(), SLOT(updatePhysics()));
	connect(m_scene.getJelly().getDrawTimer(), SIGNAL(timeout()), &m_scene, SLOT(draw()));
	connect(m_scene.getJelly().getDrawTimer(), SIGNAL(timeout()), ui.openGLWidget, SLOT(update()));
	//connect(this, SIGNAL(startSimulation()), &m_scene.getJelly(), SLOT(updatePhysics()));

	ui.openGLWidget->setRenderer(m_scene.getRenderer());
	//m_scene.initializeScene();
}
