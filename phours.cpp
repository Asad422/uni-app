#include "phours.h"
#include "ui_phours.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QComboBox>


phours::phours(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::phours)
{
    ui->setupUi(this);

    initData(); // load all data first

    // add days to dropdown
    ui->comboBox->addItem("Monday");
    ui->comboBox->addItem("Tuesday");
    ui->comboBox->addItem("Wednesday");
    ui->comboBox->addItem("Thursday");
    ui->comboBox->addItem("Friday");

    // connect dropdown to our function
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &phours::onDayChanged);

    // setup table columns
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "Professor" << "Time" << "Duration" << "Room";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setVisible(false);

    // show monday by default
    onDayChanged(0);
}

phours::~phours()
{
    delete ui;
}

void phours::onDayChanged(int index)
{
    if (index < 0) return; // just in case

    // get day name from dropdown
    QString day = ui->comboBox->currentText();
    displayDay(day);
}

void phours::displayDay(const QString &day)
{
    // clear table first
    ui->tableWidget->setRowCount(0);

    // go through all slots and show only selected day
    for (const ProfSlot &s : allSlots) {
        if (s.day != day) continue; // skip other days

        // add new row
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        // fill cells
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(s.professor));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(s.start + " - " + s.end));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(s.duration));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(s.room));

        // center all cells
        for (int c = 0; c < 4; c++)
            ui->tableWidget->item(row, c)->setTextAlignment(Qt::AlignCenter);
    }
}

void phours::initData()
{
    // all professor slots from schedule
    // format: professor, day, start, end, duration, room

    allSlots = {
                // monday
                {"Ubaydullaeva Umida",   "Monday", "11:00", "12:00", "60 min", "A413"},
                {"Khodieva Gulmira",     "Monday", "13:30", "14:30", "60 min", "A406"},
                {"Lee Seulki",           "Monday", "13:30", "14:30", "60 min", "A409"},
                {"Tashkhodjayev Rustam", "Monday", "13:30", "14:30", "60 min", "A411"},
                {"Yusupov Jaloliddin",   "Monday", "14:30", "15:30", "60 min", "A402"},
                {"Sariqulov Furqat",     "Monday", "16:30", "17:30", "60 min", "A405"},
                {"Tukhtaev Bakhtier",    "Monday", "18:00", "18:30", "30 min", "A412"},

                // tuesday
                {"Seth Kirti",           "Tuesday", "09:30", "10:00", "30 min", "A410"},
                {"Asranov Mansur",       "Tuesday", "10:00", "11:00", "60 min", "A403"},
                {"Dragunov Andrei",      "Tuesday", "11:00", "12:00", "60 min", "A404"},
                {"Makhamedova Shirin",   "Tuesday", "14:00", "15:00", "60 min", "A413"},
                {"Atamurotov Farrukh",   "Tuesday", "14:30", "15:30", "60 min", "A412"},
                {"Khankeldiev Khasan",   "Tuesday", "16:00", "16:30", "30 min", "A414"},

                // wednesday
                {"Lee Keun Jung",        "Wednesday", "09:30", "10:30", "60 min", "A412"},
                {"Lee Dongwon",          "Wednesday", "10:30", "11:30", "60 min", "A402"},
                {"Safarov Utkir",        "Wednesday", "11:00", "11:30", "30 min", "A413"},
                {"Khidayatova Gulkhumor","Wednesday", "12:30", "13:30", "60 min", "A402"},
                {"Lee June Sup",         "Wednesday", "12:30", "13:00", "30 min", "A406"},
                {"Musurmonova Parvina",  "Wednesday", "12:30", "13:00", "30 min", "A413"},
                {"Kim Heungsang",        "Wednesday", "13:30", "14:30", "60 min", "A415"},
                {"Turgunova Shakhnoze",  "Wednesday", "16:30", "17:30", "60 min", "A404"},
                {"Saydasheva Angelina",  "Wednesday", "17:30", "18:30", "60 min", "A401"},

                // thursday
                {"Isamukhamedova Ozoda", "Thursday", "09:30", "10:00", "30 min", "A402"},
                {"Turakulov Valijon",    "Thursday", "10:00", "11:00", "60 min", "A403"},
                {"Minhaz Uddin Ahmed",   "Thursday", "12:00", "13:00", "60 min", "A401"},
                {"Neyaskulova Rano",     "Thursday", "12:30", "13:00", "30 min", "A408"},
                {"Ahmedhanov Ahad",      "Thursday", "15:00", "15:30", "30 min", "A410"},
                {"Ditta Allah",          "Thursday", "15:30", "16:30", "60 min", "A408"},
                {"Seth Ashish",          "Thursday", "15:30", "16:00", "30 min", "A403"},
                {"Abdullaev Sarvar",     "Thursday", "16:00", "16:30", "30 min", "A406"},
                {"Khodjayev Jasurbek",   "Thursday", "16:00", "16:30", "30 min", "A407"},
                {"An Chongkoo",          "Thursday", "18:00", "18:30", "30 min", "A412"},

                // friday
                {"Eraliev Ovbek",        "Friday", "09:30", "10:30", "60 min", "A413"},
                {"Nurullaev Azam",       "Friday", "10:00", "10:30", "30 min", "A402"},
                {"Suvanov Sharof",       "Friday", "10:00", "10:30", "30 min", "A407"},
                {"Askarova Ayjamal",     "Friday", "10:30", "11:30", "60 min", "A416"},
                {"Hong Jeong",           "Friday", "13:00", "14:00", "60 min", "A411"},
                {"Muratov Bobir",        "Friday", "16:00", "17:00", "60 min", "A416"},
                {"Tarawade Abhijit",     "Friday", "16:30", "17:00", "30 min", "A415"},
                {"Kenesbaev Sultan",     "Friday", "18:00", "19:00", "60 min", "A409"},
                };
}