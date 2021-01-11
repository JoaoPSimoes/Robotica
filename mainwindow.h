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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_bebida_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_button_manual_clicked();

    void on_button_clean_clicked();

    void on_button_menu_clicked();

    void on_cuba_button_clicked();

    void on_gin_button_clicked();

    void on_vodka_button_clicked();

    void on_caipirinha_button_clicked();

    void on_label_bebida_linkActivated(const QString &link);

    void on_button_ok_clicked();

    void on_button_wisckey_clicked();

    void on_button_gin_clicked();

    void on_button_vodka_clicked();

    void on_button_cola_clicked();

    void on_button_tonica_clicked();

    void on_button_redbul_clicked();

    void on_button_limpar_clicked();

    void on_button_bebida_ok_clicked();

private:
    Ui::MainWindow *ui;
    QString Receita;
};
#endif // MAINWINDOW_H
