#include "database.h"

#include <QUrl>
#include <QStandardPaths>
#include <QTextStream>
#include <QSqlQuery>
#include <QStringList>
#include <QPixmap>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
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
    createStationsTable();
    createStationCategoriesTable();
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


bool KadioDatabase::createStationsTable()
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS Stations"
        "(id INTEGER PRIMARY KEY"
        ",title TEXT NOT NULL"
        ",url TEXT NOT NULL"
        ",image_url TEXT"
        ",image_blob BLOB"
        ",description TEXT"
        ",date_added TEXT DEFAULT (datetime('now'))"
        ",country TEXT) STRICT"
    ));
    return execute(query);
}


bool KadioDatabase::createStationCategoriesTable()
{
    QSqlQuery query;
    query.prepare(QStringLiteral(
        "CREATE TABLE IF NOT EXISTS StationCategories"
        "(id INTEGER PRIMARY KEY"
        ",station_id TEXT NOT NULL"
        ",category TEXT NOT NULL) STRICT"
    ));
    return execute(query);
}


bool KadioDatabase::addStation(const QString& title, const QUrl& url, const QStringList& tags, const QPixmap& img)
{
    QSqlQuery qmain;
    qmain.prepare(QStringLiteral("INSERT INTO Stations(title, url, image_blob) VALUES (:title, :url, :image_blob)"));
    qmain.bindValue(QStringLiteral(":title"), title);
    qmain.bindValue(QStringLiteral(":url"), url);

    QByteArray blob;
    QBuffer buffer{&blob};
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");
    buffer.close();

    qmain.bindValue(QStringLiteral(":image_blob"), blob);
    if (! execute(qmain)) {
        return false;
    }

    if (! tags.isEmpty()) {
        const int last_id = qmain.lastInsertId().toInt();
        QSqlQuery qtag;
        qtag.prepare(QStringLiteral("INSERT INTO StationCategories(station_id, category) VALUES (:station_id, :category)"));
        qtag.bindValue(QStringLiteral(":station_id"), last_id);
        for (const QString& tag : tags) {
            if (tag.isEmpty()) {
                continue;
            }
            qtag.bindValue(QStringLiteral(":category"), tag);
            if (! execute(qtag)) {
                return false;
            }
        }
    }
    return true;
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
    execute(query);
    query.prepare(QStringLiteral("DROP TABLE StationCategories"));
    execute(query);

    if (! createStationsTable()) { return false; }
    if (! createStationCategoriesTable()) { return false; }
    return true;
}
