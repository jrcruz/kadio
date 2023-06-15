#pragma once

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QUrl>



class LocalStationModalPopup : public QDialog
{
    Q_OBJECT

private:
    QString _title;
    QUrl _url;
    QStringList _tags;
    QPixmap _img;

public:
    explicit LocalStationModalPopup(QWidget* parent);

    QString title() const;
    QUrl url() const;
    QStringList tags() const;
    QPixmap image() const;
};
