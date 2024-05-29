#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "GlobalApplication.h"
#include "testWindow.h"

int main(int argc, char *argv[])
{
   /* GlobalApplication* app = new GlobalApplication(argc, argv);
    MainWindow w(app);
    w.show();
    return app->exec();*/
   
    
    QApplication a(argc, argv);
    testWindow w;
    w.show();
    return a.exec();
}
