#pragma once


class QString;
class QStringList;
class QSqlQuery;
class QUrl;
class QPixmap;


class KadioDatabase
{

public:
    [[nodiscard]] static KadioDatabase& instance()
    {
        static KadioDatabase instance;
        return instance;
    }

    bool addStation(const QString& title, const QUrl& url, const QStringList& tags, const QPixmap& image);
    bool clearStations();

private:
    bool createStationsTable();
    bool createStationCategoriesTable();

private:
    KadioDatabase();
    ~KadioDatabase();
    KadioDatabase(const KadioDatabase&) = delete;
    KadioDatabase(KadioDatabase&&) = delete;
    bool execute(QSqlQuery&);
};
