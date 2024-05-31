#pragma once

#include <QMainWindow>
#include "ui_testWindow.h"
#include "CustomTreeWidget.h"
#include "Word.h"
#include <QLabel>

class testWindow : public QMainWindow
{
	Q_OBJECT

public:
	testWindow(QWidget *parent = nullptr);
	~testWindow();

	void onSelWordChanged(QString);
	QLabel* selWord;
	Word* wdblank;

private:
	Ui::testWindowClass ui;
};
