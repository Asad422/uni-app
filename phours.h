#ifndef PHOURS_H
#define PHOURS_H

#include <QDialog>
#include <QString>
#include <QVector>

namespace Ui {
class phours;
}

// one professor working slot
struct ProfSlot {
    QString professor; // professor name
    QString day;       // Mon/Tue/Wed/Thu/Fri
    QString start;     // start time like "11:00"
    QString end;       // end time like "12:00"
    QString duration;  // how long
    QString room;      // room number
};

class phours : public QDialog
{
    Q_OBJECT

public:
    explicit phours(QWidget *parent = nullptr);
    ~phours();

private slots:
    void onDayChanged(int index); // when user picks a day

private:
    Ui::phours *ui;
    QVector<ProfSlot> allSlots; // all professor slots

    void initData();                          // fill data here
    void displayDay(const QString &day);      // show selected day
};

#endif