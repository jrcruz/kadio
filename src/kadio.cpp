#include "kadio.h"
#include "station_list_item.h"
#include "database.h"
#include "local_station_modal_popup.h"

#include <QCoreApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAction>
#include <QStatusBar>
#include <QFileDialog>
#include <QInputDialog>

#include <QtDebug>
#include <QSaveFile>
#include <QDateTime>
#include <QPixmap>
#include <QBuffer>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QSqlQuery>

#include <KActionCollection>
#include <KLocalizedString>


kadio::kadio(QWidget *parent) :
    KXmlGuiWindow(parent)
{
    QWidget* window = new QWidget(this);
    QHBoxLayout* main_layout = new QHBoxLayout(window);

    left_pane = new QWidget;
    main_layout->addWidget(left_pane);
    QVBoxLayout* left_pane_layout = new QVBoxLayout(left_pane);

    QSqlQuery q{KadioDatabase::instance().selectStationIdTitleUrlImage()};
    while (q.next()) {
        QStringList tags;
        tags.reserve(5);
        QSqlQuery tags_query{KadioDatabase::instance().selectStationCategories(q.value(0).toInt())};
        while (tags_query.next()) {
            tags.append(tags_query.value(0).toString());
        }

        QPixmap image;
        image.loadFromData(q.value(3).toByteArray());

        auto line = new StationListItem(q.value(1).toString(), q.value(2).toUrl(), tags, image);
        connect(line, &StationListItem::labelClicked, this, &kadio::changeTrack);
        left_pane_layout->addWidget(line);
    }

    play_button = new QPushButton(QIcon::fromTheme(QStringLiteral("media-playback-start")), i18n("Play"));
    main_layout->addWidget(play_button);
    connect(play_button, &QPushButton::clicked, this, &kadio::playPauseMedia);

    QAction* new_station = new QAction(QIcon::fromTheme(QStringLiteral("document-new")), i18n("&New station"), this);
    this->actionCollection()->addAction(QStringLiteral("new-station"), new_station);
    this->actionCollection()->setDefaultShortcut(new_station, Qt::CTRL + Qt::Key_N);
    connect(new_station, &QAction::triggered, this, &kadio::addNewStation);

    QAction* import_stations = new QAction(QIcon::fromTheme(QStringLiteral("document-import")), i18n("&Import stations"), this);
    this->actionCollection()->addAction(QStringLiteral("import-stations"), import_stations);
    connect(import_stations, &QAction::triggered, this, &kadio::importStations);

    QAction* export_stations = new QAction(QIcon::fromTheme(QStringLiteral("document-export")), i18n("&Export stations"), this);
    this->actionCollection()->addAction(QStringLiteral("export-stations"), export_stations);
    connect(export_stations, &QAction::triggered, this, &kadio::exportStations);

    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());

    this->setCentralWidget(window);

    mediaplayer = new QMediaPlayer(this);

    QStatusBar* status_bar = new QStatusBar(window);
    status_bar->addPermanentWidget(new QLabel);
    this->setStatusBar(status_bar);

    this->setupGUI(Default, QStringLiteral("kadioui.rc"));
}


void kadio::playPauseMedia()
{
    if (mediaplayer->media().isNull()) {
        return;
    }

    if (mediaplayer->state() == QMediaPlayer::PlayingState) {
        mediaplayer->pause();
        play_button->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-start")));
        play_button->setText(i18n("Play"));
    }
    else {
        mediaplayer->play();
        play_button->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-pause")));
        play_button->setText(i18n("Pause"));
    }
}


void kadio::changeTrack(StationListItem* clicked_label)
{
    mediaplayer->setMedia(clicked_label->url());
    mediaplayer->play();
    play_button->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-pause")));
    play_button->setText(i18n("Pause"));
    this->statusBar()->findChild<QLabel*>()->setText(clicked_label->title());
}


void kadio::addNewStation()
{
    LocalStationModalPopup d{this};
    if (d.exec() == QDialog::Rejected) {
        return;
    }

    if (d.url().isValid() && (d.url().scheme() == "http" || d.url().scheme() == "https")) {
        auto list_item = new StationListItem(d.title(), d.url(), d.tags(), d.image());
        left_pane->layout()->addWidget(list_item);
        connect(list_item, &StationListItem::labelClicked, this, &kadio::changeTrack);

        KadioDatabase::instance().addStation(d.title(), d.url(), d.tags(), d.image());
    }
}


void kadio::importStations()
{
    // Select and read previously exported file.
    QString export_file_path = QFileDialog::getOpenFileName(this, i18n("Select Kadio export file"), getenv("HOME"), i18n("JSON file (*.json)"));
    if (export_file_path.isEmpty()) {
        return;
    }

    QFile export_file(export_file_path);
    export_file.open(QIODevice::ReadOnly);
    auto json_document = QJsonDocument::fromJson(export_file.readAll());
    export_file.close();

    // Clear current station list.
    auto labels = left_pane->findChildren<StationListItem*>();
    for (StationListItem* label_pointer : labels) {
        delete label_pointer;
    }
    KadioDatabase::instance().clearStations();

    // Read station data from exported file and create new entries.
    // Store them in the database.
    auto items = json_document["entries"].toArray();
    for (auto entry_value : items) {
        QJsonObject entry = entry_value.toObject();

        QString title = entry["title"].toString();
        QUrl url = entry["url"].toString();

        QStringList tags;
        tags.reserve(5);
        auto tags_array = entry["tags"].toArray();
        for (auto tag : tags_array) {
            tags.append(tag.toString());
        }

        // Load image from base64-encoded string in the export file.
        QByteArray base64_image_bytes;
        QTextStream{&base64_image_bytes} << entry["image"].toString();
        QPixmap image;
        auto conversion_result = QByteArray::fromBase64Encoding(base64_image_bytes);
        if (conversion_result) {
            image.loadFromData(*conversion_result);
        }
        else {
            qDebug() << "Failed to base64 decode image for station '" << title << "'. Loading default icon.";
            image.load(QStringLiteral(":/default-radio-icon"));
        }

        auto list_item = new StationListItem(title, url, tags, image);
        left_pane->layout()->addWidget(list_item);
        connect(list_item, &StationListItem::labelClicked, this, &kadio::changeTrack);

        KadioDatabase::instance().addStation(title, url, tags, image);
    }
    this->statusBar()->showMessage(i18n("Successfully imported %1 stations").arg(items.size()), 3000);
}


void kadio::exportStations()
{
    QJsonObject top_level;

    QString current_time = QDateTime::currentDateTimeUtc().toString(QStringLiteral("yyyy-MM-dd'T'HH:mm:ss"));
    top_level.insert(QStringLiteral("export_date"), current_time);

    QJsonArray item_array;
    auto labels = left_pane->findChildren<StationListItem*>();
    for (StationListItem* label : labels) {
        QJsonObject station_entry;
        station_entry.insert(QStringLiteral("title"), label->title());
        station_entry.insert(QStringLiteral("url"), label->url().toString());
        station_entry.insert(QStringLiteral("tags"), QJsonArray::fromStringList(label->tags()));

        QByteArray image_bytes;
        QBuffer buffer{&image_bytes};
        buffer.open(QIODevice::WriteOnly);
        label->image().save(&buffer, "PNG");
        station_entry.insert(QStringLiteral("image"), QString{image_bytes.toBase64()});

        item_array.append(station_entry);
    }
    top_level.insert(QStringLiteral("entries"), item_array);

    QJsonDocument json_document(top_level);

    QString default_export_file_name;
    QTextStream{&default_export_file_name} << getenv("HOME") << "/export_kadio.json";
    QString export_file_path = QFileDialog::getSaveFileName(this, i18n("Export file"), default_export_file_name, i18n("JSON file (*.json)"));
    if (export_file_path.isEmpty()) {
        return;
    }

    QSaveFile out_file{export_file_path};
    out_file.open(QIODevice::WriteOnly);
    out_file.write(json_document.toJson());
    out_file.commit();
    this->statusBar()->showMessage(i18n("Successfully exported station list"), 3000);
}
