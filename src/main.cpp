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
    KLocalizedString::setApplicationDomain("kadio");

    KAboutData about_data(
        QStringLiteral("kadio"), // Component name
        i18n("Kadio"), // Display name
        QStringLiteral("1.0"), // Version
        i18n("Qt-based web radio"), // Short description
        KAboutLicense::GPL_V3, // Licence type
        i18n("Copyright 2023, João Cruz"), // Copyright statement
        QStringLiteral(""), // Other text
        QStringLiteral("https://jcruz.eu/tags/kadio/") // Home page address
    );
    about_data.addAuthor(
        i18n("João Cruz"), // Name
        i18n("Main Developer"), // Task
        QStringLiteral("jcruz@posteo.net"), // E-mail address
        QStringLiteral("https://jcruz.eu/")); // Web address
    KAboutData::setApplicationData(about_data);


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

