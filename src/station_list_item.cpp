#include "station_list_item.h"

#include <QMouseEvent>
#include <QHBoxLayout>


StationListItem::StationListItem(const QString& label_text, const QUrl& url, const QStringList& tags, const QPixmap& image)
    : _title{label_text}
    , _url{url}
    , _tags{tags}
    , _image{image.scaled({48, 48}, Qt::IgnoreAspectRatio)}
{
    this->resize(400, 300);
    this->setGeometry(QRect(0, 0, 300, 70));
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    auto station_name = new QLabel(this);
    station_name->setGeometry(QRect(70, 8, 200, 20));
    station_name->setText(_title);

    auto station_image = new QLabel(this);
    station_image->setGeometry(QRect(10, 10, 48, 48));
    station_image->setPixmap(_image);

    //auto horizontalLayoutWidget = new QWidget(this);
    //horizontalLayoutWidget->setGeometry(QRect(70, 31, 201, 30));

    //auto horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    //horizontalLayout->setContentsMargins(0, 0, 0, 0);
}


QString StationListItem::title() const
{ return _title; }


QUrl StationListItem::url() const
{ return _url; }


QStringList StationListItem::tags() const
{ return _tags; }


QPixmap StationListItem::image() const
{ return _image; }


void StationListItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit labelClicked(this);
    }
}
