#include "kadio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    kadio w;
    w.show();

    return app.exec();
}

