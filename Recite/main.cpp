#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "GlobalApplication.h"

int main(int argc, char *argv[])
{
    GlobalApplication* app = new GlobalApplication(argc, argv);
    MainWindow w(app);
    w.show();
    return app->exec();
}
