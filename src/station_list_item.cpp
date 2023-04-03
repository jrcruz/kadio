#include "station_list_item.h"

#include <QMouseEvent>


StationListItem::StationListItem(const QString& label_text, const QUrl& url)
    : QLabel(label_text)
    , m_url(url)
{
    ;
}


StationListItem::~StationListItem() = default;


void StationListItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit labelClicked(this);
    }
}


const QUrl& StationListItem::url() const
{
    return m_url;
}
