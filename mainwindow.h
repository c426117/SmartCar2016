#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <Windows.h>
#include <tchar.h>
#include "bmp.h"

#define COMBUF 76800
#define READBUF 4800

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    int serial_init ();

    int get_bmpdata ();

private slots:
    void on_pushButton_start_clicked();
    void timerupdate ();
    void on_comboBox_com_activated(const QString &arg1);

    void on_comboBox_px_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString comname;
    HANDLE hcomf;
    char* bmpdata;
    double n;//获取图像次数
    bmp mybmp;
    int w,h;//图像的宽和高
};

#endif // MAINWINDOW_H
