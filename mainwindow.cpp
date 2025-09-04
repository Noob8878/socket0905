#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTcpserver>
#include<QtNetwork>
MainWindow::MainWindow(QWidget *parent) ://定义构造函数
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 /* QTcpServer  *mserver=new QTcpServer;
    mserver->listen(QHostAddress::Any,0); */


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonstart_clicked()
{
     mserver=new QTcpServer(this);
     QObject::connect(mserver,&QTcpServer::newConnection,this,[&](){
     //客服端连接字
     msocket=mserver->nextPendingConnection();

     QObject::connect(msocket,&QTcpSocket::readyRead,this,[&](){
         QByteArray arr=msocket->readAll();

         QString str(arr);

    ui->lineEdit->setText(str);

     });
      });
    mserver->listen(QHostAddress::Any,ui->spinBox->value());


}

void MainWindow::on_pushButtonsend_clicked()
{      QString str=ui->lineEdit_2->text();

    //   QByteArray arr;
    QByteArray arr = str.toUtf8();
     //  arr.append(str);
     //  arr.append(str);
        msocket->write(arr);

}
