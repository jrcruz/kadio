#pragma once

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QPicture>
#include <QUrl>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>



class LocalStationModalPopup : public QDialog
{
    Q_OBJECT

public:

    explicit LocalStationModalPopup(QWidget* parent);
    void setupUi();

    QString _title;
    QUrl _url;
    QLabel _img;
    QStringList _tags;
};
