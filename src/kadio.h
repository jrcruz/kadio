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

public:
    explicit kadio(const QVector<QString>& words, QWidget *parent = nullptr);
    ~kadio() override;
};
