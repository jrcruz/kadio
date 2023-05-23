#pragma once


class QString;
class QSqlQuery;
class QUrl;


class KadioDatabase
{

public:
    [[nodiscard]] static KadioDatabase& instance()
    {
        static KadioDatabase instance;
        return instance;
    }

    bool addStation(const QString& title, const QUrl& url);
    QSqlQuery selectStationTitleUrl();
    bool clearStations();

private:
    bool createStations();

private:
    KadioDatabase();
    ~KadioDatabase();
    KadioDatabase(const KadioDatabase&) = delete;
    KadioDatabase(KadioDatabase&&) = delete;
    bool execute(QSqlQuery&);
};
