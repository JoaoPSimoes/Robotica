#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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

    void on_plus_dose_clicked();

    void on_menos_dose_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capture;
    cv::Mat frame;
    QString Receita;

    int State;
    int id_bebida;
    int n_dose;
    MyVideoCapture *mOpenCV_VideoCapture;


};
#endif // MAINWINDOW_H
