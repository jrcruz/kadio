#include "kadio.h"
#include "ui_kadio.h"

kadio::kadio(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::kadio)
{
    m_ui->setupUi(this);
}

kadio::~kadio() = default;
