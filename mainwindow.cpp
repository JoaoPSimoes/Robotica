#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    Receita="";

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
    Receita=Receita+"-Wisckey\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_gin_clicked()
{
    Receita=Receita+"-Gin\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_vodka_clicked()
{
    Receita=Receita+"-Vodka\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_cola_clicked()
{
    Receita=Receita+"-Coca-Cola\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_tonica_clicked()
{
    Receita=Receita+"-Água Tónica\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
}

void MainWindow::on_button_redbul_clicked()
{
    Receita=Receita+"-RedBull\n";
    ui->label_receita->setText(Receita);
    ui->label_receita->setStyleSheet("color:white");
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
