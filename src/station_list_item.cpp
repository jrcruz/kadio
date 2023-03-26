#include "station_list_item.h"

#include <QMouseEvent>


StationListItem::StationListItem(const QString& label_text)
    : QLabel(label_text)
{
    ;
}


StationListItem::~StationListItem() = default;


void StationListItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit labelClicked(this->text());
    }
}
