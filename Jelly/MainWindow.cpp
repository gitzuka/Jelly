#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connectUi();
	initializeProgram();
}

MainWindow::~MainWindow()
{
}

void MainWindow::processKey(QKeyEvent* event)
{
	switch(event->key())
	{
	case 'Q':
		emit qKeyPressed();
		break;
	default:
		break;
	}
}

void MainWindow::connectUi()
{
	connect(ui.doubleSpinBox_c1, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setc1(double)));
	connect(ui.doubleSpinBox_c2, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setc2(double)));
	connect(ui.doubleSpinBox_k, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setk(double)));
	connect(ui.doubleSpinBox_mass, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setMasses(double)));
	connect(ui.doubleSpinBox_VRange, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setVelocitiesRange(double)));
	connect(ui.doubleSpinBox_PosRange, SIGNAL(valueChanged(double)), &m_scene.getJelly(), SLOT(setPositionsRange(double)));
	connect(ui.pushButton_randomV, SIGNAL(clicked()), &m_scene.getJelly(), SLOT(randomVelocities()));
	connect(ui.pushButton_randomPos, SIGNAL(clicked()), &m_scene.getJelly(), SLOT(randomVelocities()));
	connect(this, SIGNAL(cursorCheckboxToggled(int)), &m_scene, SLOT(setCursorDrawState(int)));
	connect(this, SIGNAL(cursorCheckboxToggled(int)), ui.openGLWidget, SLOT(setCursorState(int)));
	connect(ui.checkBox_points, SIGNAL(stateChanged(int)), &m_scene, SLOT(setPointsDrawState(int)));
	connect(ui.checkBox_frame, SIGNAL(stateChanged(int)), &m_scene, SLOT(setFrameDrawState(int)));
	connect(ui.checkBox_jelly, SIGNAL(stateChanged(int)), &m_scene, SLOT(setJellyDrawState(int)));
	connect(ui.checkBox_cursor, SIGNAL(stateChanged(int)), ui.openGLWidget, SLOT(setCursorState(int)));
	connect(ui.checkBox_cuboid, SIGNAL(stateChanged(int)), &m_scene, SLOT(setCuboidDrawState(int)));
	connect(ui.checkBox_bezier, SIGNAL(stateChanged(int)), &m_scene, SLOT(setBezierDrawState(int)));
	connect(ui.checkBox_model, SIGNAL(stateChanged(int)), &m_scene, SLOT(setModelDrawState(int)));

	connect(ui.openGLWidget, SIGNAL(initializedGL()), &m_scene, SLOT(initializeScene()));
	connect(ui.openGLWidget, SIGNAL(paintedGL()), &m_scene, SLOT(draw()));
	connect(ui.openGLWidget, SIGNAL(leftMouseClicked(float, float, bool, float, float, bool)), &m_scene, SLOT(moveFrame(float, float, bool, float, float, bool)));
	connect(ui.openGLWidget, SIGNAL(initRotation(float, float)), &m_scene, SLOT(rotateFrame(float, float)));
	connect(ui.openGLWidget, SIGNAL(paintedGL()), &m_scene, SLOT(draw()));

	//connect(&m_scene.getJelly(), SIGNAL(simulationUpdated(int)), &m_scene, SLOT(draw(int)));
	connect(&m_scene, SIGNAL(frameMoved(std::shared_ptr<CubeFrame>)), &m_scene.getJelly(), SLOT(updateFramePosition(std::shared_ptr<CubeFrame>)));
	connect(&m_scene, SIGNAL(cursorPosUpdated(const QVector3D&)), this, SLOT(updateCursorLabel(const QVector3D&)));
	connect(m_scene.getJelly().getPhysicsTimer(), SIGNAL(timeout()), &m_scene.getJelly(), SLOT(updatePhysics()));
	//connect(m_scene.getJelly().getDrawTimer(), SIGNAL(timeout()), &m_scene, SLOT(draw()));
	connect(m_scene.getJelly().getDrawTimer(), SIGNAL(timeout()), ui.openGLWidget, SLOT(update()));

	connect(this, SIGNAL(qKeyPressed()), this, SLOT(toggleCursorCheckobx()));
	connect(ui.openGLWidget, SIGNAL(keyPressed(QKeyEvent*)), this, SLOT(processKey(QKeyEvent*)));

	ui.openGLWidget->setRenderer(m_scene.getRenderer());
}

void MainWindow::initializeProgram()
{
	m_scene.getJelly().startSimulation();
	m_cursorLabelText = ui.label_cursor->text();
}

void MainWindow::updateCursorLabel(const QVector3D& pos) const
{
	ui.label_cursor->setText(m_cursorLabelText +
		QString::number(pos.x(),'f', 3) + " " + QString::number(pos.y(), 'f', 3) + " " + QString::number(pos.z(), 'f', 3));
}

void MainWindow::toggleCursorCheckobx() const
{
	ui.checkBox_cursor->setChecked(!ui.checkBox_cursor->isChecked());
	emit cursorCheckboxToggled(ui.checkBox_cursor->isChecked());
}
