#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAX_DOSES_BEBIDA 3

#define TIMEOUT_COMMS 4000


#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>


#include <iostream>

using namespace std;

namespace Ui
{
class MainWindow;
}
class MyVideoCapture;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_bebida_clicked();

    void on_button_manual_clicked();

    void on_button_clean_clicked();

    void on_button_menu_clicked();

    void on_cuba_button_clicked();

    void on_gin_button_clicked();

    void on_vodka_button_clicked();

    void on_caipirinha_button_clicked();

    void on_button_ok_clicked();

    void on_button_wisckey_clicked();

    void on_button_gin_clicked();

    void on_button_vodka_clicked();

    void on_button_cola_clicked();

    void on_button_tonica_clicked();

    void on_button_redbul_clicked();

    void on_button_limpar_clicked();

    void on_button_bebida_ok_clicked();

    void on_camera_ON_clicked();

    void on_take_snapshot_clicked();

    void on_lavar_copo_clicked();

    void on_button_sevenup_clicked();

    void on_button_cerveja_clicked();

    void on_button_groselha_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capture;
    cv::Mat frame;
    QString Receita;

    int State;
    int id_bebida;
    float coordenadas_copo_x;
    float coordenadas_copo_y;
    MyVideoCapture *mOpenCV_VideoCapture;
    QTcpSocket socketClient;
    uint Num_Doses_Cerveja;
    uint Num_Doses_Groselha;
    uint Num_Doses_7UP;

};
#endif // MAINWINDOW_H
