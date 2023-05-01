#include "database.h"
#include <QStandardPaths>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

KadioDatabase::KadioDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    QString file_name;
    QTextStream(&file_name) << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                            << QStringLiteral("/kadio.db");
    db.setDatabaseName(file_name);
    if (! db.open()) {
        auto err = db.lastError();
        qDebug() << err.text();
        exit(1);
    }
    createStations();
}


KadioDatabase::~KadioDatabase()
{
    QSqlDatabase::database().close();
}


bool KadioDatabase::execute(QSqlQuery& query)
{
    if (! query.exec()) {
        auto err = query.lastError();
        qDebug() << err.text();
        return false;
    }
    return true;
}


bool KadioDatabase::createStations()
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS Stations"
        "(id INTEGER PRIMARY KEY"
        ",title TEXT NOT NULL"
        ",url TEXT NOT NULL"
        ",image_url TEXT"
        ",description TEXT"
        ",date_added TEXT DEFAULT (datetime('now'))"
        ",country TEXT) STRICT"
    ));
    return execute(query);
}


bool KadioDatabase::addStation(const QString& title, const QString& url)
{
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO Stations(title, url) VALUES (:title, :url)"));
    query.bindValue(QStringLiteral(":title"), title);
    query.bindValue(QStringLiteral(":url"), url);
    return execute(query);
}


QSqlQuery KadioDatabase::selectStationTitleUrl()
{
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT title, url FROM Stations"));
    execute(query);
    return query;
}


bool KadioDatabase::clearStations()
{
    QSqlQuery query;
    query.prepare(QStringLiteral("DROP TABLE Stations"));
    if (! execute(query)) {
        return false;
    }
    return createStations();
}

