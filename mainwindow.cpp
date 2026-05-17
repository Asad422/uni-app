#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "timetable.h"
#include "phours.h"

void MainWindow::on_phours_clicked()
{
    // open professor hours window
    phours *w = new phours(this);
    w->setWindowTitle("Professor Hours");
    w->exec();
}
#include "attendance.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // setup ui from designer file
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timetable_clicked()
{
    // create and open timetable dialog
    timetable *w = new timetable(this);
    w->setWindowTitle("Time Table");
    w->exec();
}



void MainWindow::on_attendance_clicked()
{
    attendance *w = new attendance(this);
    w->setWindowTitle("Attendance");
    w->exec();
}