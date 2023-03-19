#include <QApplication>
#include <KAboutData>
#include <KLocalizedString>

#include "kadio.h"


#include <KDatePicker>
#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    kadio* w = new kadio ;
    w->show();

/*
    QWidget* top = new QWidget;
    QHBoxLayout* t = new QHBoxLayout(top);
    QLabel* q = new QLabel("Karen");
    QLabel* p = new QLabel("Senjougahara");
    t->addWidget(p, 0, Qt::AlignHCenter	);
    t->addWidget(q, 0, Qt::AlignHCenter	);
    top->show();
*/
    return app.exec();
}

