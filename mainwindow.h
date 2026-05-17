#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // open timetable window
    void on_timetable_clicked();

    // open professor hours window
    void on_phours_clicked();

    // open attendance window
    void on_attendance_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H