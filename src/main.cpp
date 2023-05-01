#include <QApplication>
#include <KAboutData>
#include <KLocalizedString>

#include "kadio.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("kadio");

    KAboutData about_data(
        QStringLiteral("kadio"), // Component name
        i18n("Kadio"), // Display name
        QStringLiteral("1.0"), // Version
        i18n("Qt-based web radio"), // Short description
        KAboutLicense::GPL_V3, // License type
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

    kadio w;
    w.show();
    return app.exec();
}

