#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QDialog>
#include <QCheckBox>
#include <QMap>
#include <QStringList>
#include <QVector>

namespace Ui {
class attendance;
}

struct Student {
    QString id;
    QString name;
};

class attendance : public QDialog
{
    Q_OBJECT

public:
    explicit attendance(QWidget *parent = nullptr);
    ~attendance();

private slots:
    void onGroupChanged(const QString &group);
    void onExportClicked();

private:
    void initStudentData();

    Ui::attendance *ui;
    QMap<QString, QVector<Student>> groupStudents;
    QVector<QCheckBox*> checkBoxes;
};

#endif // ATTENDANCE_H
