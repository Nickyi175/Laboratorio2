#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_1_clicked();

    void on_btn_triangulo_clicked();

    void on_btn_back1_clicked();

    void on_btn_back1_2_clicked();

    void on_btn_2_clicked();

    void on_btn_valid_clicked();

    void on_btn_back1_3_clicked();

    void on_btn_3_clicked();

    void on_btn_salir_clicked();

    void on_btn_convertir_clicked();

    void on_comboBox_conversiones_activated(int index);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
