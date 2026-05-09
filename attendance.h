#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QDialog>

namespace Ui {
class attendance;
}

class attendance : public QDialog
{
    Q_OBJECT

public:
    explicit attendance(QWidget *parent = nullptr);
    ~attendance();

private:
    Ui::attendance *ui;
};

#endif // ATTENDANCE_H
