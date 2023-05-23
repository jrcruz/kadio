#pragma once

#include <QLabel>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QPixmap>


class QMouseEvent;


class StationListItem : public QLabel
{
    Q_OBJECT

private:
    QUrl _url;
    QStringList _tags;
    QPixmap _image;

public:
    explicit StationListItem(QString label_text, QUrl url, QStringList tags, QPixmap image);
    ~StationListItem() = default;

    QString title() const;
    QUrl url() const;
    QStringList tags() const;
    QPixmap image() const;

    void mousePressEvent(QMouseEvent* event) override;

signals:
    void labelClicked(StationListItem*);
};
