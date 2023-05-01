#include "kadio.h"
#include "station_list_item.h"
#include "database.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAction>
#include <QCoreApplication>
#include <QStatusBar>
#include <QFileDialog>
#include <QInputDialog>

#include <KActionCollection>
#include <KLocalizedString>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QDateTime>

#include <QSqlQuery>


kadio::kadio(QWidget *parent) :
    KXmlGuiWindow(parent)
{
    QWidget* window = new QWidget(this);
    QHBoxLayout* main_layout = new QHBoxLayout(window);

    left_pane = new QWidget;
    main_layout->addWidget(left_pane);
    QVBoxLayout* left_pane_layout = new QVBoxLayout(left_pane);

    QSqlQuery q = KadioDatabase::instance().selectStationTitleUrl();
    while (q.next()) {
        auto line = new StationListItem(q.value(0).toString(), q.value(1).toUrl());
        connect(line, &StationListItem::labelClicked, this, &kadio::changeTrack);
        left_pane_layout->addWidget(line);
    }

    play_button = new QPushButton(QIcon::fromTheme("media-playback-start"), "Play");
    main_layout->addWidget(play_button);
    connect(play_button, &QPushButton::clicked, this, &kadio::playPauseMedia);

    QAction* new_station = new QAction(QIcon::fromTheme("document-new"), i18n("&New station"), this);
    this->actionCollection()->addAction("new-station", new_station);
    this->actionCollection()->setDefaultShortcut(new_station, Qt::CTRL + Qt::Key_N);
    connect(new_station, &QAction::triggered, this, &kadio::addNewStation);

    QAction* import_stations = new QAction(QIcon::fromTheme("document-import"), i18n("&Import stations"), this);
    this->actionCollection()->addAction("import-stations", import_stations);
    connect(import_stations, &QAction::triggered, this, &kadio::importStations);

    QAction* export_stations = new QAction(QIcon::fromTheme("document-export"), i18n("&Export stations"), this);
    this->actionCollection()->addAction("export-stations", export_stations);
    connect(export_stations, &QAction::triggered, this, &kadio::exportStations);

    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());

    this->setCentralWidget(window);

    mediaplayer = new QMediaPlayer(this);

    QStatusBar* status_bar = new QStatusBar(window);
    status_bar->addPermanentWidget(new QLabel(mediaplayer->media().request().url().url()));
    this->setStatusBar(status_bar);

    this->setupGUI(Default, "kadioui.rc");
}


void kadio::playPauseMedia()
{
    if (mediaplayer->state() == QMediaPlayer::PlayingState) {
        mediaplayer->pause();
        play_button->setIcon(QIcon::fromTheme("media-playback-start"));
        play_button->setText("Play");
    }
    else {
        mediaplayer->play();
        play_button->setIcon(QIcon::fromTheme("media-playback-pause"));
        play_button->setText("Pause");
    }
}


void kadio::changeTrack(StationListItem* clicked_label)
{
    mediaplayer->setMedia(QUrl(clicked_label->url()));
    mediaplayer->play();
    play_button->setIcon(QIcon::fromTheme("media-playback-pause"));
    play_button->setText("Pause");
    this->statusBar()->findChild<QLabel*>()->setText(clicked_label->text());
}


void kadio::addNewStation()
{
    bool ok = false;
    QString url_string = QInputDialog::getText(this, "Add station", "Web radio URL:", QLineEdit::Normal, "https://", &ok);
    QUrl url(url_string);
    if (ok && url.isValid() && (url.scheme() == "http" || url.scheme() == "https")) {
        auto list_item = new StationListItem(url_string, url);
        left_pane->layout()->addWidget(list_item);
        connect(list_item, &StationListItem::labelClicked, this, &kadio::changeTrack);
        KadioDatabase::instance().addStation(url_string, url_string);
        changeTrack(list_item);
    }
}


void kadio::importStations()
{
    QString export_file_path = QFileDialog::getOpenFileName(this, i18n("Select Kadio export file"), getenv("HOME"), i18n("Json file (*.json)"));
    if (export_file_path.isEmpty()) {
        return;
    }

    QFile export_file(export_file_path);
    export_file.open(QIODevice::ReadOnly);
    auto json_document = QJsonDocument::fromJson(export_file.readAll());
    export_file.close();

    // Clear current list.
    auto labels = left_pane->findChildren<StationListItem*>();
    for (auto label_pointer : labels) {
        delete label_pointer;
    }
    KadioDatabase::instance().clearStations();

    auto items = json_document["entries"].toArray();
    for (auto entry_value : items) {
        QJsonObject entry = entry_value.toObject();
        QString title = entry["title"].toString();
        QString url = entry["url"].toString();

        auto list_item = new StationListItem(title, url);
        left_pane->layout()->addWidget(list_item);
        connect(list_item, &StationListItem::labelClicked, this, &kadio::changeTrack);
        KadioDatabase::instance().addStation(title, url);
    }
    this->statusBar()->showMessage(QStringLiteral("Successfully imported %1 stations").arg(items.size()), 3000);
}


void kadio::exportStations()
{
    QJsonObject top_level;

    QString current_time = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd'T'HH:mm:ss");
    top_level.insert("export_date", current_time);
    QJsonArray item_array;

    auto labels = left_pane->findChildren<StationListItem*>();
    for (auto label : labels) {
        QJsonObject station_entry;
        station_entry.insert("title", label->text());
        station_entry.insert("url", label->text());
        item_array.append(station_entry);
    }
    top_level.insert("entries", item_array);

    QJsonDocument json_document(top_level);

    QString default_export_file_name;
    QTextStream(&default_export_file_name) << getenv("HOME") << "/export_kadio_" << current_time << ".json";
    QString export_file_path = QFileDialog::getSaveFileName(this, i18n("Export file"), default_export_file_name, "JSON files (*.json)");
    if (export_file_path.isEmpty()) {
        return;
    }

    QSaveFile out_file(export_file_path);
    out_file.open(QIODevice::WriteOnly);
    out_file.write(json_document.toJson());
    out_file.commit();
    this->statusBar()->showMessage("Successfully exported station list", 3000);
}


kadio::~kadio() = default;
