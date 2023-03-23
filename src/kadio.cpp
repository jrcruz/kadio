#include "kadio.h"
//#include "ui_kadio.h"
#include <KDatePicker>
#include <QDockWidget>
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

    for (const QString& w : words) {
        left_pane_layout->addWidget(new QLabel(w));
    }

    QLabel* right_pane = new QLabel("four");
    main_layout->addWidget(right_pane);

    this->setCentralWidget(window);

    QMediaPlayer* mediaplayer = new QMediaPlayer(this);
    mediaplayer->setMedia(QUrl::fromLocalFile("/home/cruz/kadio/Cantique de Noël.mp3"));
    mediaplayer->play();
}


}

kadio::~kadio() = default;
