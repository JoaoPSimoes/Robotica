#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QTcpSocket>
#include <QTime>
#include "myvideocapture.h"

using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    Receita="";
    State=0;
    id_bebida=0;
    n_dose=0;

    mOpenCV_VideoCapture=new MyVideoCapture(this);
    connect(mOpenCV_VideoCapture, &MyVideoCapture::newPixmpapCaptured,this,[&]()
    {
        ui->video_label->setPixmap(mOpenCV_VideoCapture->pixmap().scaled(500,500));
    });





    /*  const int Timeout = 5 * 1000;
        QTime readtime;

        QTcpSocket socketClient;
        socketClient.connectToHost("192.168.40.128", 7000);
        readtime.start();


        if (!socketClient.waitForConnected(Timeout)) {
            qDebug() << "Timeout connection!";

        }


}
QByteArray formatMsg(QByteArray msg, unsigned short idMsg){

    const char READVARIABLE=0;

    QByteArray header, block;
    int lunghezza,varNameLen;
    unsigned char hByte, lByte;
    unsigned char hByteMsg,lByteMsg;

    varNameLen=msg.size();
    hByte=(varNameLen & 0xff00) >> 8;
    lByte=(varNameLen & 0x00ff);

    block.append(READVARIABLE).append(hByte).append(lByte).append(msg);
    lunghezza=block.size();

    hByte=(lunghezza & 0xff00) >> 8;
    lByte=(lunghezza & 0x00ff);

    // Message ID ( MAX: 0xFFFF )
    hByteMsg=(idMsg & 0xff00) >> 8;
    lByteMsg=(idMsg & 0x00ff);

    header.append(hByteMsg).append(lByteMsg).append(hByte).append(lByte);
    block.prepend(header);

    qDebug()<<"Message send:"<<block.toHex();

    return block;
}
QByteArray formatMsg(QByteArray msg, QByteArray value, unsigned short idMsg){

    const char WRITEVARIABLE=1;

    QByteArray header, block;
    short lunghezza,varNameLen,varValueLen;
    unsigned char hByte, lByte;
    unsigned char hByteMsg,lByteMsg;

    varNameLen=msg.size();
    hByte=(varNameLen & 0xff00) >> 8;
    lByte=(varNameLen & 0x00ff);

    block.append(WRITEVARIABLE).append(hByte).append(lByte).append(msg);

    varValueLen=value.size();
    hByte=(varValueLen & 0xff00) >> 8;
    lByte=(varValueLen & 0x00ff);

    block.append(hByte).append(lByte).append(value);

    lunghezza=block.size();

    hByte=(lunghezza & 0xff00) >> 8;
    lByte=(lunghezza & 0x00ff);

    hByteMsg=(idMsg & 0xff00) >> 8;
    lByteMsg=(idMsg & 0x00ff);

    header.append(hByteMsg).append(lByteMsg).append(hByte).append(lByte);
    block.prepend(header);

    qDebug()<<"Message send:"<<block.toHex();

    return block;
}

unsigned short clearMsg(QByteArray msg, QByteArray &value){

    short lenMsg,func,lenValue;
    unsigned short idReadMsg;

    if(msg.size() > 0){
        //Message ID
        idReadMsg=((unsigned char)msg[0])<<8 | ((unsigned char)msg[1]);
        qDebug() << "Message ID: " << idReadMsg;

        //Message Length
        lenMsg=((unsigned char)msg[2])<<8 | ((unsigned char)msg[3]);
        qDebug() << "Message Length:" << lenMsg;

        //Function(read:0/Write:1)
        func=((int)msg[4]);
        qDebug() << "Function(read:0/Write:1) " << func;

        //Value Length
        lenValue=((unsigned char)msg[5])<<8 | ((unsigned char)msg[6]);
        qDebug() << "Value Length:" << lenValue;

        qDebug() << "Message return:" << msg.toHex();

        // the byte7 begin the value
        value = msg.mid(7,lenValue);
        return idReadMsg;

    }
    else{
        value = QByteArray("");
        return 0;
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_bebida_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_button_manual_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_button_clean_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_button_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_Ingredientes->setText("");
    ui->label_bebida->setText("");
    ui->label_receita->setText("");
    ui->label_bebida_a->setText("");
    ui->label_preparar->setText("");


}

void MainWindow::on_cuba_button_clicked()
{
    ui->label_bebida->setText("Cuba Livre");
    ui->label_bebida->setStyleSheet("color:white");
    ui->label_Ingredientes->setText("-Wisckey\n-Coca-Cola\n-Gelo\n-Limão");
    ui->label_Ingredientes->setStyleSheet("color:white");
}

void MainWindow::on_gin_button_clicked()
{
    ui->label_bebida->setText("Gin Tónico");
    ui->label_bebida->setStyleSheet("color:white");
    ui->label_Ingredientes->setText("-Gin\n-Água Tónica\n-Gelo\n-Limão");
    ui->label_Ingredientes->setStyleSheet("color:white");
}

void MainWindow::on_vodka_button_clicked()
{
    ui->label_bebida->setText("Vodka Laranja");
    ui->label_bebida->setStyleSheet("color:white");
    ui->label_Ingredientes->setText("-Vodka\n-Sumo de Laranja\n-Gelo");
    ui->label_Ingredientes->setStyleSheet("color:white");
}

void MainWindow::on_caipirinha_button_clicked()
{
    ui->label_bebida->setText("Caipirinha");
    ui->label_bebida->setStyleSheet("color:white");
    ui->label_Ingredientes->setText("-Cachaça\n-Gelo\n-Lima");
    ui->label_Ingredientes->setStyleSheet("color:white");
}



void MainWindow::on_button_ok_clicked()
{
    ui->label_preparar->setText("A preparar bebida...");
    ui->label_preparar->setStyleSheet("color:orange");
}

void MainWindow::on_button_wisckey_clicked()
{
    if(id_bebida!=1)
    {
        n_dose=1;
        Receita=Receita+"-Wisckey -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        ui->label_receita->setStyleSheet("color:white");
        id_bebida=1;
    }

}

void MainWindow::on_button_gin_clicked()
{
    if(id_bebida!=2)
    {
        n_dose=1;
        Receita=Receita+"-Gin - \n";
        ui->label_receita->setText(Receita);
        ui->label_receita_2->setText(QString::number(n_dose)+" dose\n");
        ui->label_receita->setStyleSheet("color:white");
        ui->label_receita_2->setStyleSheet("color:white");
        id_bebida=2;

    }
}

void MainWindow::on_button_vodka_clicked()
{
    if(id_bebida!=3)
    {
        n_dose=1;
        Receita=Receita+"-Vodka -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        ui->label_receita_2->setStyleSheet("color:white");
        ui->label_receita->setStyleSheet("color:white");
        id_bebida=3;

    }
}

void MainWindow::on_button_cola_clicked()
{
    if(id_bebida!=4)
    {
        n_dose=1;
        Receita=Receita+"-Coca-Cola -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        ui->label_receita->setStyleSheet("color:white");
        id_bebida=4;
    }
}

void MainWindow::on_button_tonica_clicked()
{
    if(id_bebida!=5)
    {
        n_dose=1;
        Receita=Receita+"-Água Tónica -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        ui->label_receita->setStyleSheet("color:white");
        id_bebida=5;

    }
}

void MainWindow::on_button_redbul_clicked()
{
    if(id_bebida!=6)
    {
        n_dose=1;
        Receita=Receita+"-RedBull -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        ui->label_receita->setStyleSheet("color:white");
        id_bebida=6;

    }
}

void MainWindow::on_button_limpar_clicked()
{
    Receita="";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_bebida_ok_clicked()
{
    ui->label_bebida_a->setText("A preparar bebida...");
    ui->label_bebida_a->setStyleSheet("color:orange");
}



/*
void MainWindow::on_camera_ON_clicked(bool)
{


    if (State==0)
    {
        mCamera->start();
        State=1;
        cout<<"Chegou";
        ui->camera_ON->setStyleSheet("border-image: url(:/imagens/camera_on.png);");
    }else if(State==1){
        State=0;
        mCamera->stop();
        ui->camera_ON->setStyleSheet("border-image: url(:/imagens/camera_off.png);");
    }


}
*/



void MainWindow::on_camera_ON_clicked()
{
    if (State==0)
    {
        State=1;
        ui->camera_ON->setStyleSheet("border-image: url(:/imagens/camera_on.png);");

        mOpenCV_VideoCapture->start(QThread::HighestPriority);

    }
    else if (State==1)
    {
        State=0;
        ui->camera_ON->setStyleSheet("border-image: url(:/imagens/camera_off.png);");
        mOpenCV_VideoCapture->terminate();
    }


}


void MainWindow::on_plus_dose_clicked()

{
    n_dose=n_dose+1;
    switch (id_bebida)

    {
    case 1:
        Receita=Receita+"-Wisckey -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);

        break;
    case 2:
        Receita=Receita+"-Gin -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;

    case 3:
        Receita=Receita+"-Vodka -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 4:
        Receita=Receita+"-Coca-Cola -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 5:
        Receita=Receita+"-Água Tónica -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 6:
        Receita=Receita+"-RedBull -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    default:
        break;
    }


}

void MainWindow::on_menos_dose_clicked()
{
    n_dose=n_dose-1;
    switch (id_bebida)

    {
    case 1:
        Receita=Receita+"-Wisckey -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);

        break;
    case 2:
        Receita=Receita+"-Gin -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;

    case 3:
        Receita=Receita+"-Vodka -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 4:
        Receita=Receita+"-Coca-Cola -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 5:
        Receita=Receita+"-Água Tónica -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    case 6:
        Receita=Receita+"-RedBull -" + QString::number(n_dose)+" dose\n";
        ui->label_receita->setText(Receita);
        break;
    default:
        break;
    }

}
