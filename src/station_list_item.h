#pragma once

#include <QLabel>


class QMouseEvent;


class StationListItem : public QLabel
{
    Q_OBJECT

public:
    explicit StationListItem(const QString& label_text);
    ~StationListItem () override;

    void mousePressEvent(QMouseEvent* event) override;

signals:
    void labelClicked(const QString& my_text);
};
