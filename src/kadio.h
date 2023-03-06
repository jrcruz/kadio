#ifndef KADIO_H
#define KADIO_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class kadio;
}

class kadio : public QMainWindow
{
    Q_OBJECT

public:
    explicit kadio(QWidget *parent = nullptr);
    ~kadio() override;

private:
    QScopedPointer<Ui::kadio> m_ui;
};

#endif // KADIO_H
