#include <QApplication>
#include "kadio.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    kadio* w = new kadio;
    w->show();

    return app.exec();
}

