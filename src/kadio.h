#pragma once

#include <KXmlGuiWindow>

class QPushButton;
class QMediaPlayer;
class StationListItem;


class kadio : public KXmlGuiWindow
{
    Q_OBJECT

private:
    QMediaPlayer* mediaplayer;
    QPushButton* play_button;
    QWidget* left_pane;

public slots:
    void playPauseMedia();
    void changeTrack(StationListItem* clicked_label);
    void addNewStation();
    void importStations();
    void exportStations();

public:
    explicit kadio(QWidget *parent = nullptr);
    ~kadio() override;
};
