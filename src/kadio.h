#ifndef KADIO_H
#define KADIO_H

#include <QMainWindow>
#include <QScopedPointer>

class kadio : public QMainWindow
{
    Q_OBJECT

public:
    explicit kadio(QWidget *parent = nullptr);
    ~kadio() override;

};

#endif // KADIO_H
