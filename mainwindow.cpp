#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QTcpSocket>
#include <QTime>
#include <QApplication>
#include "myvideocapture.h"
#include "ImageProc.h"


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
    coordenadas_copo_x = 0.0;
    coordenadas_copo_y = 0.0;
    Num_Doses_Cerveja = 0;
    Num_Doses_Groselha = 0;
    Num_Doses_7UP = 0;
    ui->video_label->setScaledContents(true);
    //ui->snapshot->setScaledContents(true);
    mOpenCV_VideoCapture=new MyVideoCapture(this);
    connect(mOpenCV_VideoCapture, &MyVideoCapture::newPixmpapCaptured,this,[&]()
    {
        ui->video_label->setPixmap(mOpenCV_VideoCapture->pixmap());
    });

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
    }
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
    ui->erro_mixing->setText("");
    ui->msg_arrumar->setText("");
    ui->label_preparar->setText("");
    Receita="";
    ui->label_receita->setText(Receita);
    Num_Doses_7UP = 0;
    Num_Doses_Cerveja = 0;
    Num_Doses_Groselha = 0;
    ui->label_5->setText("Copos identificados:");
    coordenadas_copo_x = 0;
    coordenadas_copo_y = 0;
    mOpenCV_VideoCapture->terminate();
    ui->snapshot->setStyleSheet("background-color: rgb(0, 0, 0);");


}

void MainWindow::on_cuba_button_clicked()
{   
    ui->label_preparar->setText("");
    id_bebida = 1;
    ui->label_bebida->setText("Cuba Livre");
    ui->label_Ingredientes->setText("-Whisky\n-Coca-Cola\n-Gelo\n-Limão");
}

void MainWindow::on_gin_button_clicked()
{   
    ui->label_preparar->setText("");
    id_bebida = 2;
    ui->label_bebida->setText("Gin Tónico");
    ui->label_Ingredientes->setText("-Gin\n-Água Tónica\n-Gelo\n-Limão");
}

void MainWindow::on_vodka_button_clicked()
{   
    ui->label_preparar->setText("");
    id_bebida = 3;
    ui->label_bebida->setText("Vodka Laranja");
    ui->label_Ingredientes->setText("-Vodka\n-Sumo de Laranja\n-Gelo");
}

void MainWindow::on_caipirinha_button_clicked()
{   
    ui->label_preparar->setText("");
    id_bebida = 4;
    ui->label_bebida->setText("Caipirinha");
    ui->label_Ingredientes->setText("-Cachaça\n-Gelo\n-Lima");
}
void MainWindow::on_groselha_button_clicked()
{
    ui->label_preparar->setText("");
    id_bebida = 5;
    ui->label_bebida->setText("Groselha");
    ui->label_Ingredientes->setText("-Groselha\n-7up\n-Gelo");
}

void MainWindow::on_cerveja_button_clicked()
{
    ui->label_preparar->setText("");
    id_bebida = 6;
    ui->label_bebida->setText("Cerveja");
    ui->label_Ingredientes->setText("-Cerveja");
}

void MainWindow::on_button_ok_clicked()
{
ui->label_preparar->setText("");
qApp->processEvents();
    switch (id_bebida)
    {
    case 0:
        //não fazer nada
        break;
    case 1:
         ui->label_preparar->setText("Bebida Indisponível!");
        break;
    case 2:
        ui->label_preparar->setText("Bebida Indisponível!");
        break;
    case 3:
        ui->label_preparar->setText("Bebida Indisponível!");
        break;
    case 4:
        ui->label_preparar->setText("Bebida Indisponível!");
        break;
    case 5:{
        ui->label_preparar->setText("A preparar bebida...");
        qApp->processEvents();
        QTcpSocket socketClient;
        socketClient.connectToHost("192.168.10.254", 7000);
        if (!socketClient.waitForConnected(TIMEOUT_COMMS)) {
            ui->erro_mixing->setText("Ocorreu uma falha de conexão.\nTente de novo por favor...");
            cout<<"Erro na conexao"<<endl;
            return;}

        //Groselha
        socketClient.write(formatMsg("NUM_PORTIONS_1",QByteArray::number(1),43981));
        if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
            ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
            cout<<"Erro no envio"<<endl;
            return;}

        //7up
        socketClient.write(formatMsg("NUM_PORTIONS_2",QByteArray::number(2),43981));
        if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
            ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
            cout<<"Erro no envio"<<endl;
            return;}
        socketClient.disconnectFromHost();

        break;
    }
    case 6: {

        ui->label_preparar->setText("A preparar bebida...");
        qApp->processEvents();

        QTcpSocket socketClient;
        socketClient.connectToHost("192.168.10.254", 7000);
        if (!socketClient.waitForConnected(TIMEOUT_COMMS)) {
            ui->erro_mixing->setText("Ocorreu uma falha de conexão.\nTente de novo por favor...");
            cout<<"Erro na conexao"<<endl;
            return;}
        //Cerveja
        socketClient.write(formatMsg("NUM_PORTIONS_3",QByteArray::number(3),43981));
        if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
            ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
            cout<<"Erro no envio"<<endl;
            return;}
        socketClient.disconnectFromHost();

        break;
    }
    }
    id_bebida = 0;
}

void MainWindow::on_button_limpar_clicked()
{
    Receita="";
    ui->erro_mixing->setText("");
    ui->label_receita->setText(Receita);
    Num_Doses_7UP = 0;
    Num_Doses_Cerveja = 0;
    Num_Doses_Groselha = 0;
}

void MainWindow::on_button_bebida_ok_clicked()
{
    if(Num_Doses_Groselha==0 && Num_Doses_7UP==0 && Num_Doses_Cerveja==0){
        ui->erro_mixing->setText("Por favor escolha as dosagens");
        return;
    }
    ui->erro_mixing->setText("A preparar bebida...");
    qApp->processEvents();

    QTcpSocket socketClient;
    socketClient.connectToHost("192.168.10.254", 7000);
    if (!socketClient.waitForConnected(TIMEOUT_COMMS)) {
        ui->erro_mixing->setText("Ocorreu uma falha de conexão.\nTente de novo por favor...");
        cout<<"Erro na conexao"<<endl;
        return;}


    socketClient.write(formatMsg("NUM_PORTIONS_1",QByteArray::number(Num_Doses_Groselha),43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.write(formatMsg("NUM_PORTIONS_2",QByteArray::number(Num_Doses_7UP),43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.write(formatMsg("NUM_PORTIONS_3",QByteArray::number(Num_Doses_Cerveja),43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.write(formatMsg("Flag_Tirar_Bebida","TRUE",43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->erro_mixing->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.disconnectFromHost();
    ui->erro_mixing->setText("Sucesso!");

}

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

void MainWindow::on_take_snapshot_clicked()
{
    ui->msg_arrumar->setText("A segmentar a mesa...");
    qApp->processEvents();

    int h_upper_mesa = 79;
    int h_lower_mesa = 56;
    int s_upper_mesa = 255;
    int s_lower_mesa = 40;
    int v_upper_mesa = 255;
    int v_lower_mesa = 40;

    int h_upper_copo = 255;
    int h_lower_copo = 0;
    int s_upper_copo = 110;
    int s_lower_copo = 20;
    int v_upper_copo = 168;
    int v_lower_copo = 20;

    Mat captured = mOpenCV_VideoCapture->frame();
    //Mat captured = imread("D://cop_2.jpg");
    Mat blur;
    GaussianBlur(captured, blur, Size(5, 5), 0);
    Mat segm_mesa = VCPI_Segmenta_Cor(blur,h_lower_mesa,h_upper_mesa,s_lower_mesa,s_upper_mesa,v_lower_mesa,v_upper_mesa);	//efetuar a binarização da imagem segundo um dado threshold
    Mat binary = vcpi_gray_to_binary(vcpi_rgb_to_gray(segm_mesa), 1, 255);
    binary = vcpi_binary_open(binary, 5, Oito, 5, Oito);

    Mat temp = vcpi_get_max_blob_area(vcpi_binary_blob_improved_labelling(binary));     //filtrar blobs com tamanho inferior a um determinado numero de pixeis
    temp = vcpi_gray_negative(vcpi_get_max_blob_area(vcpi_binary_blob_improved_labelling(vcpi_gray_negative(temp))));
    temp = vcpi_binary_close(temp, 14, Oito, 16, Quatro);
    segm_mesa = apply_mask(captured, temp);

    QImage mesa( segm_mesa.data,segm_mesa.cols, segm_mesa.rows,static_cast<int>(segm_mesa.step),QImage::Format_BGR888 );
    ui->snapshot->setPixmap(QPixmap::fromImage(mesa));
    ui->msg_arrumar->setText("A segmentar o copo...");
    qApp->processEvents();

    Mat direito = corrigir_distorcao(temp,captured);
    Mat segm_copo = VCPI_Segmenta_Cor(direito, h_lower_copo, h_upper_copo, s_lower_copo, s_upper_copo, v_lower_copo, v_upper_copo);	//efetuar a binarização da imagem segundo um dado threshold
    Mat binary_copo = vcpi_gray_to_binary(vcpi_rgb_to_gray(segm_copo), 1, 255);
    binary_copo = vcpi_binary_close(binary_copo, 5, Oito, 7, Oito);
    segm_copo = apply_mask(direito, binary_copo);

    QImage copo( segm_copo.data,segm_copo.cols, segm_copo.rows,static_cast<int>(segm_copo.step),QImage::Format_BGR888 );
    ui->snapshot->setPixmap(QPixmap::fromImage(copo));
    ui->msg_arrumar->setText("A encontrar coordenadas...");
    qApp->processEvents();

    Mat labels = vcpi_binary_blob_improved_labelling(binary_copo);
    binary_copo = vcpi_filter_blob_area(labels, 200);
    labels = vcpi_binary_blob_improved_labelling(binary_copo);

    uint max_labels = 0;

    for (int i = 0; i < labels.cols * labels.rows; i++) {
        max_labels = labels.data[i] > max_labels ? labels.data[i] : max_labels;
    }

    coordenadas cent_copo = vcpi_blob_centroid(find_replace_value(labels, 1, 255));
    //cout << "Img size pixels X: " << direito.cols << "  Y: " << direito.rows<<endl;
    //cout << "Pixel pos copo X: " << cent_copo.x << "    Y: " << cent_copo.y << "  Area: "<< cent_copo.area <<endl;
    float pos_copo_y =(float) (416.0f / (float)direito.rows)*cent_copo.y;
    float pos_copo_x =(float) (346.0f / (float)direito.cols)*cent_copo.x;

    //warp correction
    float half_rows = (float)direito.rows/2.0f;
    float correctionFactor = ((float)cent_copo.y-half_rows)/((float) half_rows);
    pos_copo_y -= 32.0f*correctionFactor;
    cout << "Millimetros copo X: " << pos_copo_x << "  Y: " << pos_copo_y << endl;

    //trocar as coordenadas após a conversão
    coordenadas_copo_x = pos_copo_y;
    coordenadas_copo_y = pos_copo_x;

    Mat out = find_apply_created(direito, find_create_with(vcpi_draw_circle_centroid(find_replace_value(labels, 1, 255)), 255, 40, 40, 255));

    QImage image( out.data,out.cols, out.rows,static_cast<int>(out.step),QImage::Format_BGR888 );
    ui->snapshot->setPixmap(QPixmap::fromImage(image));

    QString text = "Copos Identificados: ";
    text.append(QString::number(1));
    text.append("\nCoordenadas:\n\tX:");
    text.append(QString::number(pos_copo_x,'f',2));
    text.append("\n\tY:");
    text.append(QString::number(pos_copo_y,'f',2));
    ui->label_5->setText(text);
    ui->msg_arrumar->setText("Análise visual completa");

}

void MainWindow::on_lavar_copo_clicked()
{
    if(coordenadas_copo_x==0 && coordenadas_copo_y==0){
        ui->msg_arrumar->setText("Por favor execute a análise visual");
        return;
    }

    QByteArray msg = "{X ";
    QByteArray x = QByteArray::number(coordenadas_copo_x,'f',2);
    QByteArray y = QByteArray::number(coordenadas_copo_y,'f',2);

    msg.append(x);
    msg.append(",Y ");
    msg.append(y);
    msg.append(",Z 0.0,A 93.23,B 1.4,C 1.83}");

    ui->msg_arrumar->setText("A arrumar copo...");
    qApp->processEvents();

    cout<<"Coordenadas enviadas ao KUKA"<<endl;
    cout<<msg.toStdString()<<endl;

    QTcpSocket socketClient;
    socketClient.connectToHost("192.168.10.254", 7000);
    if (!socketClient.waitForConnected(TIMEOUT_COMMS)) {
        ui->msg_arrumar->setText("Ocorreu uma falha de conexão.\nTente de novo por favor...");
        cout<<"Erro na conexao"<<endl;
        return;}

    socketClient.write(formatMsg("G3_sistema_visao",msg,43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->msg_arrumar->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.write(formatMsg("Flag_Arrumar_Copo","TRUE",43981));
    if(!socketClient.waitForBytesWritten(TIMEOUT_COMMS)) {
        ui->msg_arrumar->setText("Ocorreu uma falha de comunicação.\nTente de novo por favor...");
        cout<<"Erro no envio"<<endl;
        return;}

    socketClient.disconnectFromHost();
    ui->msg_arrumar->setText("Sucesso");

}

void MainWindow::on_button_sevenup_clicked()
{
    if((Num_Doses_Groselha + Num_Doses_7UP + Num_Doses_Cerveja)< 3){
        Num_Doses_7UP++;
        Receita=Receita+"+1 dose   7-Up \n";
        ui->label_receita->setText(Receita);
    }
}

void MainWindow::on_button_cerveja_clicked()
{
    if((Num_Doses_Groselha + Num_Doses_7UP + Num_Doses_Cerveja)< 3){
        Num_Doses_Cerveja++;
        Receita=Receita+"+1 dose   Cerveja \n";
        ui->label_receita->setText(Receita);
    }
}

void MainWindow::on_button_groselha_clicked()
{
    if((Num_Doses_Groselha + Num_Doses_7UP + Num_Doses_Cerveja)< 3){
        Num_Doses_Groselha++;
        Receita=Receita+"+1 dose   Groselha \n";
        ui->label_receita->setText(Receita);
    }

}


