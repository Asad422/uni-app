#include "timetable.h"
#include "ui_timetable.h"

timetable::timetable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::timetable)
{
    ui->setupUi(this);
}

timetable::~timetable()
{
    delete ui;
}
