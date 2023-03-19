#ifndef KADIO_H
#define KADIO_H

#include <QMainWindow>
#include <QDialog>
#include <QScopedPointer>
#include <KXmlGuiWindow>


class kadio : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit kadio(QWidget *parent = nullptr);
    ~kadio() override;

};

#endif // KADIO_H
