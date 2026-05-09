#include "phours.h"
#include "ui_phours.h"

phours::phours(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::phours)
{
    ui->setupUi(this);
}

phours::~phours()
{
    delete ui;
}
