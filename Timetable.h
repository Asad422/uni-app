#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>
#include <QString>
#include <QVector>

namespace Ui {
class timetable;
}

// lesson info
struct Lesson {
    int slot; // which pair
    QString subject; // what subject
    QString room; // where
    QString teacher; // who teaches
    QString day; // what day
};

// group info
struct Group {
    QString name; // group name like CIE-25-20
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