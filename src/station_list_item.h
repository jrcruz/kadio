#pragma once

#include <QLabel>
#include <QUrl>


class QMouseEvent;


class StationListItem : public QLabel
{
    Q_OBJECT

public:
    explicit StationListItem(const QString& label_text, const QUrl& url);
    ~StationListItem () override;

    void mousePressEvent(QMouseEvent* event) override;

    const QUrl& url() const;

signals:
    void labelClicked(StationListItem*);

private:
    QUrl m_url;
};
