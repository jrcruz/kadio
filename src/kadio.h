#pragma once

#include <KXmlGuiWindow>

class QPushButton;
class QMediaPlayer;



class kadio : public KXmlGuiWindow
{
    Q_OBJECT

private:
    QMediaPlayer* mediaplayer;
    QPushButton* play_button;

public slots:
    void playPauseMedia();
    void changeTrack(const QString& new_track);
    void addNewStation();

public:
    explicit kadio(const QVector<QString>& words, QWidget *parent = nullptr);
    ~kadio() override;
};
