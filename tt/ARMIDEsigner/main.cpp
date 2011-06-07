#include <QApplication>
#include "armidesigner.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ARMIDesigner *ide =  new ARMIDesigner;
    ide->show();
    return app.exec();
}

