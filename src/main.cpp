#include <QApplication>
#include <KAboutData>
#include <KLocalizedString>

#include "kadio.h"


#include <KDatePicker>
#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile words_file("test-file");
    if (! words_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QTextStream words_file_stream(&words_file);
    QVector<QString> words;
    while (! words_file_stream.atEnd()) {
        words.append(words_file_stream.readLine());
    }

    kadio* w = new kadio(words);
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

