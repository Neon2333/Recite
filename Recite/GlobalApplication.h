#pragma once

#include <QApplication>

class GlobalApplication  : public QApplication
{
	Q_OBJECT

public:
	GlobalApplication(int& argc, char** argv);
	~GlobalApplication();

	bool eventFilter(QObject* objcet, QEvent* event);

signals:
	void keyIPressed();	//i������
	void keyRPressed();	//r������
	void keyEnterPressed();	//enter
	void keyCtrlEnterPressed();	//alt+enter
};
