#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Scene.h"
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	Scene m_scene;
	QString m_cursorLabelText;

	void connectUi();
	void initializeProgram();

private slots:
	void updateCursorLabel(const QVector3D &pos) const;
	void toggleCursorCheckobx() const;
	void processKey(QKeyEvent *event);

signals:
	void qKeyPressed();
	void cursorCheckboxToggled(int) const;
};

#endif // JELLY_H
