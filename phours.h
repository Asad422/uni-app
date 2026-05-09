#ifndef PHOURS_H
#define PHOURS_H

#include <QDialog>

namespace Ui {
class phours;
}

class phours : public QDialog
{
    Q_OBJECT

public:
    explicit phours(QWidget *parent = nullptr);
    ~phours();

private:
    Ui::phours *ui;
};

#endif // PHOURS_H
