#ifndef JELLY_H
#define JELLY_H

#include <QtWidgets/QMainWindow>
#include "ui_jelly.h"

class Jelly : public QMainWindow
{
	Q_OBJECT

public:
	Jelly(QWidget *parent = 0);
	~Jelly();

private:
	Ui::JellyClass ui;
};

#endif // JELLY_H
