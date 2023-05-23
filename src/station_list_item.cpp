#include "station_list_item.h"

#include <QMouseEvent>


StationListItem::StationListItem(QString label_text, QUrl url, QStringList tags, QPixmap image)
    : QLabel{label_text}
    , _url{url}
    , _tags{tags}
    , _image{image}
{
    ;
}


QString StationListItem::title() const
{ return text(); }


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
