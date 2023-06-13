#include "local_station_modal_popup.h"

#include <QLabel>
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
#include <QFileDialog>
#include <QTextStream>

#include <KLocalizedString>

#include <iostream>


LocalStationModalPopup::LocalStationModalPopup(QWidget* parent)
    : QDialog(parent)
{

    this->setWindowModality(Qt::WindowModal);
    this->resize(600, 470);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(600, 400));
    this->setWindowTitle(QString::fromUtf8("Add local station"));
    this->setModal(true);
    auto verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(30, 80, 241, 271));
    auto verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    auto title_label = new QLabel(verticalLayoutWidget);
    title_label->setObjectName(QString::fromUtf8("title_label"));
    title_label->setText(QString::fromUtf8("Title*"));

    verticalLayout->addWidget(title_label);

    auto title_input = new QLineEdit(verticalLayoutWidget);
    title_input->setObjectName(QString::fromUtf8("title_input"));
    title_input->setPlaceholderText(QString::fromUtf8("Cool station name"));

    verticalLayout->addWidget(title_input);

    auto url_label = new QLabel(verticalLayoutWidget);
    url_label->setObjectName(QString::fromUtf8("url_label"));
    url_label->setText(QString::fromUtf8("URL*"));

    verticalLayout->addWidget(url_label);

    auto url_input = new QLineEdit(verticalLayoutWidget);
    url_input->setObjectName(QString::fromUtf8("url_input"));
    url_input->setPlaceholderText(QString::fromUtf8("http://example.org/radio"));

    verticalLayout->addWidget(url_input);

    auto tags_label = new QLabel(verticalLayoutWidget);
    tags_label->setObjectName(QString::fromUtf8("tags_label"));
    tags_label->setText(QString::fromUtf8("Tags"));

    verticalLayout->addWidget(tags_label);

    auto tags_input = new QLineEdit(verticalLayoutWidget);
    tags_input->setObjectName(QString::fromUtf8("tags_input"));
    tags_input->setPlaceholderText(QString::fromUtf8("rock,classical"));

    verticalLayout->addWidget(tags_input);

    auto horizontalLayoutWidget = new QWidget(this);
    horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(50, 390, 499, 40));
    auto horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    auto button_cancel = new QPushButton(horizontalLayoutWidget);
    button_cancel->setObjectName(QString::fromUtf8("button_cancel"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(button_cancel->sizePolicy().hasHeightForWidth());
    button_cancel->setSizePolicy(sizePolicy1);
    button_cancel->setMaximumSize(QSize(100, 16777215));
    QFont font;
    font.setKerning(true);
    button_cancel->setFont(font);
    button_cancel->setText(QString::fromUtf8("Cancel"));
    QIcon icon;
    QString iconThemeName = QString::fromUtf8("cancel");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon = QIcon::fromTheme(iconThemeName);
    } else {
        icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    button_cancel->setIcon(icon);
    button_cancel->setAutoDefault(false);
    button_cancel->setFlat(false);

    horizontalLayout->addWidget(button_cancel);

    auto spacer_buttons = new QSpacerItem(310, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout->addItem(spacer_buttons);

    auto button_add = new QPushButton(horizontalLayoutWidget);
    button_add->setObjectName(QString::fromUtf8("button_add"));
    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(button_add->sizePolicy().hasHeightForWidth());
    button_add->setSizePolicy(sizePolicy2);
    button_add->setMaximumSize(QSize(100, 16777215));
    button_add->setLayoutDirection(Qt::LeftToRight);
    button_add->setText(QString::fromUtf8("Add"));
    QIcon icon1;
    iconThemeName = QString::fromUtf8("add");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon1 = QIcon::fromTheme(iconThemeName);
    } else {
        icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    button_add->setIcon(icon1);
    button_add->setAutoDefault(false);

    horizontalLayout->addWidget(button_add);

    auto modal_title = new QLabel(this);
    modal_title->setObjectName(QString::fromUtf8("modal_title"));
    modal_title->setGeometry(QRect(30, 20, 222, 36));
    QFont font1;
    font1.setPointSize(16);
    modal_title->setFont(font1);
    modal_title->setText(QString::fromUtf8("Add local station"));
    auto widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(320, 91, 220, 262));
    auto verticalLayout_2 = new QVBoxLayout(widget);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    auto frame = new QFrame(widget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    auto gridLayout = new QGridLayout(frame);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    auto picture_image_label = new QLabel(frame);
    picture_image_label->setObjectName(QString::fromUtf8("picture_image_label"));
    picture_image_label->setMaximumSize(QSize(200, 200));
    picture_image_label->setPixmap(QPixmap(QString::fromUtf8(":/default-radio-icon")));
    picture_image_label->setScaledContents(true);

    gridLayout->addWidget(picture_image_label, 0, 0, 1, 1);


    verticalLayout_2->addWidget(frame);

    auto pushButton = new QPushButton(widget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setMaximumSize(QSize(115, 16777215));
    pushButton->setText(QString::fromUtf8("Add icon"));
    QIcon icon2;
    iconThemeName = QString::fromUtf8("document-import");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon2 = QIcon::fromTheme(iconThemeName);
    } else {
        icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    pushButton->setIcon(icon2);

    verticalLayout_2->addWidget(pushButton, 0, Qt::AlignHCenter);

    title_label->setBuddy(title_input);
    url_label->setBuddy(url_input);
    tags_label->setBuddy(tags_input);


    QObject::connect(button_cancel, &QAbstractButton::clicked, this, &QDialog::reject);
    QObject::connect(button_add,    &QAbstractButton::clicked, this, &QDialog::accept);

    connect(title_input, &QLineEdit::textChanged, this, [this](const QString& s) { _title = s; });
    connect(url_input,   &QLineEdit::textChanged, this, [this](const QString& s) { _url = s; });
    connect(tags_input,  &QLineEdit::textChanged, this, [this](const QString& s) { _tags = s.split(','); });
    connect(pushButton,  &QAbstractButton::clicked, this, [this, picture_image_label] {
        QPixmap image{QFileDialog::getOpenFileName(
            this, i18n("Select an image for the radio icon"),
            getenv("HOME"), "Images (*png *jpg *jpeg)"
        )};

        if (! image.isNull()) {
            _img.swap(image);
            picture_image_label->setPixmap(_img);
        }
    });

    this->show();
}


QString LocalStationModalPopup::title() const
{ return _title; }


QUrl LocalStationModalPopup::url() const
{ return _url; }


QStringList LocalStationModalPopup::tags() const
{ return _tags; }


QPixmap LocalStationModalPopup::image() const
{ return _img; }
