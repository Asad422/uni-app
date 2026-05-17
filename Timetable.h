#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>
#include <QString>
#include <QVector>

namespace Ui {
class timetable;
}

struct Lesson {
    int slot;
    int duration;
    QString subject;
    QString room;
    QString teacher;
    QString day;
};

// group info
struct Group {
    QString name;
    QVector<Lesson> lessons; // all lessons of this group
};

class timetable : public QDialog
{
    Q_OBJECT

public:
    explicit timetable(QWidget *parent = nullptr);
    ~timetable();

private slots:
    void onGroupChanged(int index); // when user picks group

private:
    Ui::timetable *ui;
    QVector<Group> groups; // all groups stored here

    void initData(); // put data here
    void displayGroup(const Group &group); // show on screen
};

#endif // TIMETABLE_H