#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //图像分辨率初始化

    ui->comboBox_px->addItem(tr("60*80"));
    ui->comboBox_px->addItem(tr("120*160"));
    ui->comboBox_px->addItem(tr("240*320"));
    w=60;
    h=80;
    ui->textBrowser_logout->append("预设分辨率 ：60*80");
    //端口选择框定义,和初始化

    ui->comboBox_com->addItem(tr("COM1"));
    ui->comboBox_com->addItem(tr("COM2"));
    ui->comboBox_com->addItem(tr("COM3"));
    ui->comboBox_com->addItem(tr("COM4"));
    ui->comboBox_com->addItem(tr("COM5"));
    ui->comboBox_com->addItem(tr("COM6"));
    ui->comboBox_com->addItem(tr("COM7"));
    ui->comboBox_com->addItem(tr("COM8"));
    ui->comboBox_com->addItem(tr("COM9"));
    ui->comboBox_com->setCurrentText(tr("COM5"));
    comname=ui->comboBox_com->currentText();
    ui->textBrowser_logout->append("预设端口为 ："+ comname);
    //设置定时器
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(timerupdate()));

    //图形缓存
    char buf[READBUF];
    bmpdata = buf;





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerupdate()
{
    if(!get_bmpdata())
    {
        mybmp.greatbmp(bmpdata);
        QImage *img = new QImage;
        img->loadFromData(mybmp.memfilep,mybmp.loffile);

    }
    else
    {

    }

}



void MainWindow::on_pushButton_start_clicked()
{
    if(serial_init())
    {
        timer->start(100);

    }
    else
    {

    }
}

void MainWindow::on_comboBox_com_activated(const QString &com)
{
    QString str = tr("选择了端口号为 ：");
    ui->textBrowser_logout->append(str+com);
    comname = com;
}

int MainWindow::serial_init ()
{

    ui->textBrowser_logout->append("尝试打开串口 "+comname);
    LPCWSTR com = (const wchar_t*)comname.utf16();
    hcomf = CreateFile(com, GENERIC_READ,0,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE ,NULL);
    if (hcomf == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hcomf);
        ui->textBrowser_logout->append("打开串口 "+comname+"失败");
        return false;
    }


    ui->textBrowser_logout->append("打开串口 "+comname+"成功");
    ui->textBrowser_logout->append("配置串口 "+comname);

    DCB comdcb;
    GetCommState(hcomf,&comdcb);
    comdcb.BaudRate = CBR_115200;
    comdcb.ByteSize = 8;
    comdcb.Parity = NOPARITY;
    comdcb.StopBits = ONESTOPBIT;
    SetCommState(hcomf,&comdcb);

    if (SetCommState(hcomf, &comdcb)!= 0)
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"成功");
        //ui->textBrowser_logout->append("配置串口 "+comname+"成功");
    }
    else
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"失败");
    }

    ui->textBrowser_logout->append("配置串口 "+comname+"缓冲区");

    if (SetupComm(hcomf, COMBUF, COMBUF) != 0)
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"缓冲区成功");
    }
    else
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"缓冲区失败");
        return false;
    }

    ui->textBrowser_logout->append("配置串口 "+comname+"超时");


    COMMTIMEOUTS comtout;
    GetCommTimeouts(hcomf,&comtout);
    comtout.ReadIntervalTimeout = 1000;
    comtout.ReadTotalTimeoutMultiplier = 500;
    comtout.ReadTotalTimeoutConstant = 5000;
    //读总超时＝ReadTotalTimeoutMultiplier×10＋ReadTotalTimeoutConstant
    comtout.WriteTotalTimeoutMultiplier = 500;
    comtout.WriteTotalTimeoutMultiplier = 2000;
    if (SetCommTimeouts(hcomf, &comtout) != 0)
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"超时成功");
    }
    else
    {
        ui->textBrowser_logout->append("配置串口 "+comname+"超时失败");
        return false;
    }

    return 0;
}


int MainWindow::get_bmpdata ()
{

    DWORD iosum;
    PurgeComm(hcomf, PURGE_RXCLEAR);
    if (ReadFile(hcomf, bmpdata, READBUF, &iosum, NULL) != 0)
    {
        QString str = QString::number(iosum,10);
        ui->textBrowser_logout->append("read : "+str +"字节");
        return 0;

    }
    else
    {
        ui->textBrowser_logout->append("读取失败");
        return 1;
    }



}

void MainWindow::on_comboBox_px_activated(const QString &px)
{
    if(px=="60*80")
    {
        ui->textBrowser_logout("选择分辨率60*80");
        w=80;
        h=60;
    }
    else if(px=="120*160")
    {
        ui->textBrowser_logout("选择分辨率120*160");
        w=160;
        h=120;
    }
    else if(px=="240*320")
    {
        ui->textBrowser_logout("选择分辨率240*320");
        w=320;
        h=240;
    }


    mybmp.bmpinit(h,w);
}
