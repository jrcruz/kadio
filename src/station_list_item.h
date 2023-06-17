#pragma once

#include <QLabel>
#include <QFrame>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QPixmap>


class QMouseEvent;


class StationListItem : public QFrame
{
    Q_OBJECT

private:
    QString _title;
    QUrl _url;
    QStringList _tags;
    QPixmap _image;

public:
    explicit StationListItem(const QString& label_text, const QUrl& url, const QStringList& tags, const QPixmap& image);
    ~StationListItem() = default;

    QString title() const;
    QUrl url() const;
    QStringList tags() const;
    QPixmap image() const;

    void mousePressEvent(QMouseEvent* event) override;

signals:
    void labelClicked(StationListItem*);
};
