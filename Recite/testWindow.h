#pragma once

#include <QMainWindow>
#include "ui_testWindow.h"

class testWindow : public QMainWindow
{
	Q_OBJECT

public:
	testWindow(QWidget *parent = nullptr);
	~testWindow();

private:
	Ui::testWindowClass ui;
};
