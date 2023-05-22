#include <QLabel>

#include "local_station_modal_popup.h"
#include <KLocalizedString>


LocalStationModalPopup::LocalStationModalPopup(QWidget* parent)
    : QDialog(parent)
{

    QLabel* l = new QLabel("hi", this);
    setupUi();
    this->show();
}


void LocalStationModalPopup::setupUi()
{
    this->setWindowModality(Qt::WindowModal);
    this->resize(600, 400);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(600, 400));
    this->setMaximumSize(QSize(600, 400));
    this->setWindowTitle(i18n("Add local station"));
    this->setModal(true);

    auto verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setGeometry(QRect(30, 80, 241, 206));
    auto verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    auto title_label = new QLabel(verticalLayoutWidget);
    title_label->setText(i18n("Title*"));

    verticalLayout->addWidget(title_label);

    auto title_input = new QLineEdit(verticalLayoutWidget);
    title_input->setPlaceholderText(i18n("Cool station name"));

    verticalLayout->addWidget(title_input);

    auto url_label = new QLabel(verticalLayoutWidget);
    url_label->setText(i18n("URL*"));

    verticalLayout->addWidget(url_label);

    auto url_input = new QLineEdit(verticalLayoutWidget);
    url_input->setPlaceholderText(i18n("http://example.org/radio"));

    verticalLayout->addWidget(url_input);

    auto tags_label = new QLabel(verticalLayoutWidget);
    tags_label->setText(i18n("Tags"));

    verticalLayout->addWidget(tags_label);

    auto tags_input = new QLineEdit(verticalLayoutWidget);
    tags_input->setPlaceholderText(i18n("rock,classical"));

    verticalLayout->addWidget(tags_input);

    auto horizontalLayoutWidget = new QWidget(this);
    horizontalLayoutWidget->setGeometry(QRect(50, 330, 499, 40));
    auto horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    auto button_cancel = new QPushButton(horizontalLayoutWidget);
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(button_cancel->sizePolicy().hasHeightForWidth());
    button_cancel->setSizePolicy(sizePolicy1);
    button_cancel->setMaximumSize(QSize(100, 16777215));
    QFont font;
    font.setKerning(true);
    button_cancel->setFont(font);
    button_cancel->setText(i18n("Cancel"));
    QIcon icon;
    QString iconThemeName = i18n("cancel");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon = QIcon::fromTheme(iconThemeName);
    } else {
        icon.addFile(i18n("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    button_cancel->setIcon(icon);
    button_cancel->setAutoDefault(false);
    button_cancel->setFlat(false);

    horizontalLayout->addWidget(button_cancel);

    auto spacer_buttons = new QSpacerItem(310, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout->addItem(spacer_buttons);

    auto button_add = new QPushButton(horizontalLayoutWidget);
    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(button_add->sizePolicy().hasHeightForWidth());
    button_add->setSizePolicy(sizePolicy2);
    button_add->setMaximumSize(QSize(100, 16777215));
    button_add->setLayoutDirection(Qt::LeftToRight);
    button_add->setText(i18n("Add"));
    QIcon icon1;
    iconThemeName = i18n("add");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon1 = QIcon::fromTheme(iconThemeName);
    } else {
        icon1.addFile(i18n("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    button_add->setIcon(icon1);
    button_add->setAutoDefault(false);

    horizontalLayout->addWidget(button_add);

    auto modal_title = new QLabel(this);
    modal_title->setGeometry(QRect(30, 20, 161, 31));
    QFont font1;
    font1.setPointSize(16);
    modal_title->setFont(font1);
    modal_title->setText(i18n("Add station"));
    auto picture_image_label = new QLabel(this);
    picture_image_label->setGeometry(QRect(330, 100, 200, 200));
    //picture_image_label->setPixmap(QPixmap(i18n("k.png")));
    auto picture_label = new QLabel(this);
    picture_label->setGeometry(QRect(390, 60, 79, 22));
    picture_label->setText(i18n("Picture"));

    title_label->setBuddy(title_input);
    url_label->setBuddy(url_input);
    tags_label->setBuddy(tags_input);

//    connect(title_input, &QLineEdit::textChanged, &_title, &QLabel::setText);
    connect(title_input, &QLineEdit::textChanged, this, [this](QString s) { _title = s; });
    connect(url_input,   &QLineEdit::textChanged, this, [this](QString s) { _url.setUrl(s); });
    connect(tags_input,  &QLineEdit::textChanged, this, [this](QString s) { _tags = s.split(','); });

    connect(button_cancel, &QAbstractButton::clicked, this, &QDialog::reject);
    connect(button_add, &QAbstractButton::clicked, this, &QDialog::accept);

    button_cancel->setDefault(false);
}
