#include "kadio.h"
#include "station_list_item.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMediaPlayer>



kadio::kadio(const QVector<QString>& words, QWidget *parent) :
    KXmlGuiWindow(parent)
{
    QWidget* window = new QWidget(this);
    QHBoxLayout* main_layout = new QHBoxLayout(window);

    QWidget* left_pane = new QWidget;
    main_layout->addWidget(left_pane);
    QVBoxLayout* left_pane_layout = new QVBoxLayout(left_pane);

    for (const QString& filename : words) {
        auto line = new StationListItem(filename);
        connect(line, &StationListItem::labelClicked, this, &kadio::changeTrack);
        left_pane_layout->addWidget(line);
    }

    play_button = new QPushButton(QIcon::fromTheme("media-pause"), "Pause");
    main_layout->addWidget(play_button);
    connect(play_button, &QPushButton::clicked, this, &kadio::playPauseMedia);

    this->setCentralWidget(window);

    mediaplayer = new QMediaPlayer(this);
    mediaplayer->setMedia(QUrl::fromLocalFile(words.first()));
    mediaplayer->play();
}


void kadio::playPauseMedia()
{
    if (mediaplayer->state() == QMediaPlayer::PlayingState) {
        mediaplayer->pause();
        play_button->setIcon(QIcon::fromTheme("media-play"));
        play_button->setText("Play");
    }
    else {
        mediaplayer->play();
        play_button->setIcon(QIcon::fromTheme("media-pause"));
        play_button->setText("Pause");
    }
}


void kadio::changeTrack(const QString& new_track)
{
    mediaplayer->setMedia(QUrl::fromLocalFile(new_track));
    mediaplayer->play();
    play_button->setIcon(QIcon::fromTheme("media-pause"));
    play_button->setText("Pause");
}


kadio::~kadio() = default;
