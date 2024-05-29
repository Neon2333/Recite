#include "GlobalApplication.h"
#include <QEvent>
#include <QKeyEvent>

GlobalApplication::GlobalApplication(int& argc, char** argv)
	: QApplication(argc, argv)
{
    // ����Ҫ��װ������
    this->installEventFilter(this);
}

GlobalApplication::~GlobalApplication()
{}

bool GlobalApplication::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_press = static_cast<QKeyEvent*>(event);
        if (key_press->key() == Qt::Key_I && !key_press->isAutoRepeat())
        {
            // �����Զ����ź�
            emit keyIPressed();
            //����
            return true;
        }
        else if (key_press->key() == Qt::Key_R && !key_press->isAutoRepeat())
        {
            emit keyRPressed();
            return true;
        }
        else if (key_press->key() == Qt::Key_Enter && !key_press->isAutoRepeat())
        {
            emit keyEnterPressed();
            return true;
        }
        else if ((key_press->key() == Qt::Key_Control && key_press->key() == Qt::Key_Enter)&& !key_press->isAutoRepeat())
        {
            emit keyCtrlEnterPressed();
            return true;
        }

    }

	return false;
}
