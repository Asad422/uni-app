#include "timetable.h"
#include "ui_timetable.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QComboBox>

timetable::timetable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::timetable)
{
    ui->setupUi(this);

    initData(); // first load all data

    // add group names to dropdown
    for (const Group &g : groups)
        ui->comboBox->addItem(g.name);

    // when user selects group call our function
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &timetable::onGroupChanged);

    // days of week for rows
    QStringList days = {"Mo", "Tu", "We", "Th", "Fr"};
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(20);
    ui->tableWidget->setVerticalHeaderLabels(days);

    // numbers 1-20 for columns
    QStringList timeslots;
    timeslots << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10"
          << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
    ui->tableWidget->setHorizontalHeaderLabels(timeslots);

    // make columns fit the text
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // show first group when program starts
    onGroupChanged(0);
}

timetable::~timetable()
{
    delete ui;
}

void timetable::onGroupChanged(int index)
{
    if (index < 0 || index >= groups.size()) return; // just in case

    displayGroup(groups[index]); // show selected group
}

void timetable::displayGroup(const Group &group)
{
    // first clean everything
    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 20; c++)
            ui->tableWidget->setItem(r, c, new QTableWidgetItem(""));

    // days to know which row to use
    QStringList days = {"Mo", "Tu", "We", "Th", "Fr"};

    // go through all lessons and put them in table
    for (const Lesson &l : group.lessons) {
        int row = days.indexOf(l.day); // find row by day name
        int col = l.slot - 1; // column is pair number minus 1

        if (row < 0 || col < 0 || col >= 20) continue; // skip if something wrong

        // text inside cell
        QString text = l.subject + "\n" + l.room + "\n" + l.teacher;

        QTableWidgetItem *item = new QTableWidgetItem(text);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, col, item);
    }
}

void timetable::initData()
{
    // here i put all schedule data for all groups
    // format is: pair number, subject, room, teacher, day

    Group g20; g20.name = "CIE-25-20";
    g20.lessons = {
                   {2,"P2","A605","R.Tashkhodjayev","Mo"},{5,"AE2","A708","A.Saydasheva","Mo"},
                   {2,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},{10,"CED","B209","O.Eraliev","Tu"},
                   {1,"CAL2","B209","U.Safarov","We"},{4,"P2","A605","R.Tashkhodjayev","We"},
                   {7,"CED","B210","O.Eraliev","We"},{2,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                   {5,"CAL2","B201","U.Safarov","Th"},{8,"PE2","A502/A504","F.Sariqulov","Th"},
                   {1,"AE2","A706","A.Saydasheva","Fr"},{4,"TWD","A705","Sh.Turgunova","Fr"},
                   }; groups.append(g20);

    Group g19; g19.name = "CIE-25-19";
    g19.lessons = {
                   {2,"P2","A605","R.Tashkhodjayev","Mo"},{5,"AE2","A708","A.Saydasheva","Mo"},
                   {2,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},{10,"CED","B209","O.Eraliev","Tu"},
                   {1,"CAL2","B209","U.Safarov","We"},{4,"P2","A605","R.Tashkhodjayev","We"},
                   {7,"CED","B210","O.Eraliev","We"},{2,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                   {5,"CAL2","B201","U.Safarov","Th"},
                   {1,"AE2","A706","A.Saydasheva","Fr"},{4,"TWD","A705","Sh.Turgunova","Fr"},
                   {10,"PE2","A502/A504","R.Tashkhodjayev","Fr"},
                   }; groups.append(g19);

    Group g18; g18.name = "CIE-25-18";
    g18.lessons = {
                   {2,"P2","A605","R.Tashkhodjayev","Mo"},
                   {2,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},{6,"AE2","A614","A.Saydasheva","Tu"},
                   {10,"CED","B209","O.Eraliev","Tu"},
                   {1,"CAL2","B209","U.Safarov","We"},{4,"P2","A605","R.Tashkhodjayev","We"},
                   {7,"CED","B210","O.Eraliev","We"},
                   {2,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},{5,"CAL2","B201","U.Safarov","Th"},
                   {8,"AE2","A407","A.Saydasheva","Th"},
                   {1,"TWD","A705","Sh.Turgunova","Fr"},{10,"PE2","A502/A504","R.Tashkhodjayev","Fr"},
                   }; groups.append(g18);

    Group g17; g17.name = "CIE-25-17";
    g17.lessons = {
                   {1,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{4,"P2","A605","R.Tashkhodjayev","Mo"},
                   {6,"AE2","A614","A.Saydasheva","Tu"},{10,"CED","B209","O.Eraliev","Tu"},
                   {1,"CAL2","B209","U.Safarov","We"},{7,"CED","B210","O.Eraliev","We"},
                   {10,"P2","A606","R.Tashkhodjayev","We"},
                   {4,"CAL2","B201","U.Safarov","Th"},{6,"AE2","A407","A.Saydasheva","Th"},
                   {1,"TWD","A705","Sh.Turgunova","Fr"},{9,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                   {13,"PE2","A502/A504","F.Atamurotov","Fr"},
                   }; groups.append(g17);

    Group g16; g16.name = "CIE-25-16";
    g16.lessons = {
                   {1,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{4,"P2","A605","R.Tashkhodjayev","Mo"},
                   {11,"AE2","B207","G.Khidayatova","Mo"},
                   {5,"TWD","A513","Sh.Turgunova","Tu"},{9,"CED","B209","O.Eraliev","Tu"},
                   {11,"AE2","B203","G.Khidayatova","Tu"},
                   {1,"CAL2","B209","U.Safarov","We"},{7,"CED","B210","O.Eraliev","We"},
                   {10,"P2","A606","R.Tashkhodjayev","We"},
                   {4,"CAL2","B201","U.Safarov","Th"},
                   {9,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                   {13,"PE2","A502/A504","R.Tashkhodjayev","Fr"},
                   }; groups.append(g16);

    Group g15; g15.name = "CIE-25-15";
    g15.lessons = {
                   {1,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{4,"P2","A605","R.Tashkhodjayev","Mo"},
                   {9,"CED","B210","O.Eraliev","Mo"},{11,"AE2","B207","G.Khidayatova","Mo"},
                   {5,"TWD","A513","Sh.Turgunova","Tu"},{11,"AE2","B203","G.Khidayatova","Tu"},
                   {7,"CAL2","B209","U.Safarov","We"},{10,"P2","A606","R.Tashkhodjayev","We"},
                   {13,"CED","B201","O.Eraliev","We"},
                   {1,"CAL2","B201","U.Safarov","Th"},
                   {5,"PE2","A502/A504","R.Tashkhodjayev","Fr"},
                   {9,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                   }; groups.append(g15);

    Group g14; g14.name = "CIE-25-14";
    g14.lessons = {
                   {1,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{4,"P2","A605","R.Tashkhodjayev","Mo"},
                   {9,"CED","B210","O.Eraliev","Mo"},
                   {2,"TWD","A513","Sh.Turgunova","Tu"},{5,"AE2","B203","G.Khidayatova","Tu"},
                   {7,"CAL2","B209","U.Safarov","We"},{10,"P2","A606","R.Tashkhodjayev","We"},
                   {13,"CED","B201","O.Eraliev","We"},
                   {1,"CAL2","B201","U.Safarov","Th"},{7,"AE2","B208","G.Khidayatova","Th"},
                   {5,"PE2","A502/A504","R.Tashkhodjayev","Fr"},
                   {9,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                   }; groups.append(g14);

    Group g13; g13.name = "CIE-25-13";
    g13.lessons = {
                   {4,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{9,"CED","B210","O.Eraliev","Mo"},
                   {15,"P2","A605","R.Tashkhodjayev","Mo"},
                   {2,"TWD","A513","Sh.Turgunova","Tu"},{5,"AE2","B203","G.Khidayatova","Tu"},
                   {13,"PE2","A502/A504","R.Tashkhodjayev","Tu"},
                   {2,"P2","A605","R.Tashkhodjayev","We"},{7,"CAL2","B209","U.Safarov","We"},
                   {13,"CED","B201","O.Eraliev","We"},
                   {1,"CAL2","B201","U.Safarov","Th"},{4,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                   {7,"AE2","B208","G.Khidayatova","Th"},
                   }; groups.append(g13);

    Group g12; g12.name = "CIE-25-12";
    g12.lessons = {
                   {4,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{9,"CED","B210","O.Eraliev","Mo"},
                   {15,"P2","A605","R.Tashkhodjayev","Mo"},
                   {9,"TWD","A513","Sh.Turgunova","Tu"},{13,"PE2","A502/A504","R.Tashkhodjayev","Tu"},
                   {2,"P2","A605","R.Tashkhodjayev","We"},{7,"CAL2","B209","U.Safarov","We"},
                   {9,"AE2","B208","G.Khidayatova","We"},{13,"CED","B201","O.Eraliev","We"},
                   {1,"CAL2","B201","U.Safarov","Th"},{4,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                   {9,"AE2","B208","G.Khidayatova","Th"},
                   }; groups.append(g12);

    Group g11; g11.name = "CIE-25-11";
    g11.lessons = {
                   {4,"OOP2","B103 PC Lab","Sh.Suvanov","Mo"},{9,"CED","B210","O.Eraliev","Mo"},
                   {15,"P2","A605","R.Tashkhodjayev","Mo"},
                   {3,"PE2","A502/A504","R.Tashkhodjayev","Tu"},{9,"TWD","A513","Sh.Turgunova","Tu"},
                   {2,"P2","A605","R.Tashkhodjayev","We"},{7,"CAL2","B209","U.Safarov","We"},
                   {9,"AE2","B208","G.Khidayatova","We"},{13,"CED","B201","O.Eraliev","We"},
                   {1,"CAL2","B201","U.Safarov","Th"},{4,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                   {9,"AE2","B208","G.Khidayatova","Th"},
                   }; groups.append(g11);

    Group g10; g10.name = "CIE-25-10";
    g10.lessons = {
                   {2,"TWD","A407","Sh.Turgunova","Mo"},{9,"CAL2","B202","U.Safarov","Mo"},
                   {11,"P2","A605","F.Atamurotov","Mo"},
                   {2,"P2","A605","F.Atamurotov","Tu"},{5,"PE2","A502/A504","F.Sariqulov","Tu"},
                   {10,"CED","B201","S.Abdullaev","Tu"},
                   {7,"AE2","B208","G.Khidayatova","We"},{9,"OOP2","B103 PC Lab","Sh.Suvanov","We"},
                   {5,"AE2","B208","G.Khidayatova","Th"},{7,"CAL2","B202","U.Safarov","Th"},
                   {1,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},{4,"CED","B201","S.Abdullaev","Fr"},
                   }; groups.append(g10);

    Group g9; g9.name = "CIE-25-09";
    g9.lessons = {
                  {2,"TWD","A407","Sh.Turgunova","Mo"},{9,"CAL2","B202","U.Safarov","Mo"},
                  {11,"P2","A605","F.Atamurotov","Mo"},
                  {2,"P2","A605","F.Atamurotov","Tu"},{10,"CED","B201","S.Abdullaev","Tu"},
                  {4,"PE2","A502/A504","F.Atamurotov","We"},{7,"AE2","B208","G.Khidayatova","We"},
                  {9,"OOP2","B103 PC Lab","Sh.Suvanov","We"},
                  {5,"AE2","B208","G.Khidayatova","Th"},{7,"CAL2","B202","U.Safarov","Th"},
                  {1,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},{4,"CED","B201","S.Abdullaev","Fr"},
                  }; groups.append(g9);

    Group g8; g8.name = "CIE-25-08";
    g8.lessons = {
                  {5,"AE2","A308","R.Neyaskulova","Mo"},{9,"CAL2","B202","U.Safarov","Mo"},
                  {11,"P2","A605","F.Atamurotov","Mo"},
                  {2,"P2","A605","F.Atamurotov","Tu"},{5,"AE2","A308","R.Neyaskulova","Tu"},
                  {10,"CED","B201","S.Abdullaev","Tu"},
                  {4,"PE2","A502/A504","F.Atamurotov","We"},{9,"OOP2","B103 PC Lab","Sh.Suvanov","We"},
                  {2,"TWD","A614","A.Saydasheva","Th"},{7,"CAL2","B202","U.Safarov","Th"},
                  {1,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},{4,"CED","B201","S.Abdullaev","Fr"},
                  }; groups.append(g8);

    Group g7; g7.name = "CIE-25-07";
    g7.lessons = {
                  {2,"P2","A607","F.Atamurotov","Mo"},{5,"AE2","A308","R.Neyaskulova","Mo"},
                  {9,"CAL2","B202","U.Safarov","Mo"},
                  {5,"AE2","A308","R.Neyaskulova","Tu"},{7,"P2","A605","F.Atamurotov","Tu"},
                  {10,"CED","B201","S.Abdullaev","Tu"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","We"},{11,"PE2","A502/A504","F.Atamurotov","We"},
                  {2,"TWD","A614","A.Saydasheva","Th"},{7,"CAL2","B202","U.Safarov","Th"},
                  {5,"CED","B201","S.Abdullaev","Fr"},{7,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                  }; groups.append(g7);

    Group g6; g6.name = "CIE-25-06";
    g6.lessons = {
                  {2,"P2","A607","F.Atamurotov","Mo"},{9,"CAL2","B202","U.Safarov","Mo"},
                  {3,"AE2","A308","R.Neyaskulova","Tu"},{7,"P2","A605","F.Atamurotov","Tu"},
                  {10,"CED","B201","S.Abdullaev","Tu"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","We"},{11,"PE2","A502/A504","F.Atamurotov","We"},
                  {2,"AE2","A608","R.Neyaskulova","Th"},{7,"CAL2","B202","U.Safarov","Th"},
                  {5,"CED","B201","S.Abdullaev","Fr"},{7,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                  {9,"TWD","A706","A.Saydasheva","Fr"},
                  }; groups.append(g6);

    Group g5; g5.name = "CIE-25-05";
    g5.lessons = {
                  {2,"P2","A607","F.Atamurotov","Mo"},{4,"CAL2","B201","U.Safarov","Mo"},
                  {3,"AE2","A308","R.Neyaskulova","Tu"},{7,"P2","A605","F.Atamurotov","Tu"},
                  {5,"CAL2","B209","U.Safarov","We"},{7,"OOP2","B103 PC Lab","Sh.Suvanov","We"},
                  {10,"CED","A203","S.Abdullaev","We"},
                  {2,"AE2","A608","R.Neyaskulova","Th"},{7,"CED","B201","S.Abdullaev","Th"},
                  {13,"PE2","A502/A504","F.Atamurotov","Th"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},{9,"TWD","A706","A.Saydasheva","Fr"},
                  }; groups.append(g5);

    Group g4; g4.name = "CIE-25-04";
    g4.lessons = {
                  {2,"P2","A607","F.Atamurotov","Mo"},{4,"CAL2","B201","U.Safarov","Mo"},
                  {2,"TWD","A501","A.Saydasheva","Tu"},{7,"P2","A605","F.Atamurotov","Tu"},
                  {1,"AE2","A706","R.Neyaskulova","We"},{5,"CAL2","B209","U.Safarov","We"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","We"},{10,"CED","A203","S.Abdullaev","We"},
                  {5,"AE2","A608","R.Neyaskulova","Th"},{7,"CED","B201","S.Abdullaev","Th"},
                  {13,"PE2","A502/A504","F.Atamurotov","Th"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","Fr"},
                  }; groups.append(g4);

    Group g3; g3.name = "CIE-25-03";
    g3.lessons = {
                  {4,"CAL2","B201","U.Safarov","Mo"},{9,"P2","A605","F.Atamurotov","Mo"},
                  {2,"TWD","A501","A.Saydasheva","Tu"},{5,"P2","A605","F.Atamurotov","Tu"},
                  {7,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},
                  {1,"AE2","A706","R.Neyaskulova","We"},{5,"CAL2","B209","U.Safarov","We"},
                  {10,"CED","A203","S.Abdullaev","We"},{15,"PE2","A502/A504","F.Atamurotov","We"},
                  {5,"AE2","A608","R.Neyaskulova","Th"},{7,"CED","B201","S.Abdullaev","Th"},
                  {9,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                  }; groups.append(g3);

    Group g2; g2.name = "CIE-25-02";
    g2.lessons = {
                  {2,"AE2","A308","R.Neyaskulova","Mo"},{5,"CAL2","B201","U.Safarov","Mo"},
                  {9,"P2","A605","F.Atamurotov","Mo"},
                  {5,"P2","A605","F.Atamurotov","Tu"},{7,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},
                  {5,"CAL2","B209","U.Safarov","We"},{6,"AE2","A706","R.Neyaskulova","We"},
                  {10,"CED","A203","S.Abdullaev","We"},{15,"PE2","A502/A504","F.Atamurotov","We"},
                  {7,"CED","B201","S.Abdullaev","Th"},{9,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                  {4,"TWD","A706","A.Saydasheva","Fr"},
                  }; groups.append(g2);

    Group g1; g1.name = "CIE-25-01";
    g1.lessons = {
                  {2,"AE2","A308","R.Neyaskulova","Mo"},{5,"CAL2","B201","U.Safarov","Mo"},
                  {9,"P2","A605","F.Atamurotov","Mo"},
                  {5,"P2","A605","F.Atamurotov","Tu"},{7,"OOP2","B103 PC Lab","Sh.Suvanov","Tu"},
                  {5,"CAL2","B209","U.Safarov","We"},{6,"AE2","A706","R.Neyaskulova","We"},
                  {10,"CED","A203","S.Abdullaev","We"},
                  {7,"CED","B201","S.Abdullaev","Th"},{9,"OOP2","B103 PC Lab","Sh.Suvanov","Th"},
                  {13,"PE2","A502/A504","F.Atamurotov","Th"},
                  {4,"TWD","A706","A.Saydasheva","Fr"},
                  }; groups.append(g1);
}