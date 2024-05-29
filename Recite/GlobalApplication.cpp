#include "GlobalApplication.h"
#include <QEvent>
#include <QKeyEvent>

GlobalApplication::GlobalApplication(int& argc, char** argv)
	: QApplication(argc, argv)
{
    // 必须要安装过滤器
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
            // 发射自定义信号
            emit keyIPressed();
            //拦截
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
