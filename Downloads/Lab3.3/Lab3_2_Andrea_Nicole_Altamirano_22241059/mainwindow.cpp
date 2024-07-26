#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_1_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_btn_back1_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->spinBox_filas->setValue(0);
    ui->textEdit->clear();

}

void MainWindow::on_btn_back1_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->resultLabel->setText("");
    ui->tarjeta->setText("");
}

void MainWindow::on_btn_2_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_btn_back1_3_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_3_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_btn_salir_clicked()
{
    QApplication::quit();
}
//EJERCICIO 2
void MainWindow::on_btn_triangulo_clicked()
{
    int filas = ui->spinBox_filas->text().toInt();
    QString triangulo;
    int ancho = 2 * filas - 1;


    for (int i = 0; i < filas; i++){
        int astericos = 2 * i + 1;
        int espacios = (ancho - astericos) / 2;

        for (int j = espacios; j >= 0; j--)
        {
            triangulo += " ";
        }
        for (int k = 1; k <= astericos; k++)
        {
            triangulo += "*";
        }
       triangulo += "\n";
    }

    ui->textEdit->setPlainText(triangulo);

}

//EJERCICIO 3 LUHN
void MainWindow::on_btn_valid_clicked()
{
    QString tarjeta = ui->tarjeta->text();

    tarjeta.replace(" ", "");
    bool validarNum = true;

    for (int i = 0; i < tarjeta.size(); i++) {
        if (!tarjeta[i].isDigit()) {
            validarNum = false;
            break;
        }
    }

    if (!validarNum) {
        QMessageBox::warning(this, "Error", "¡Error, debe ingresar solo números!");
        return;
    }

    int sumaTotal = 0;
    bool segundo = false;

    for (int i = tarjeta.size() - 1; i >= 0; i--) {
        int num = tarjeta[i].digitValue();

        if (segundo) {
            num *= 2;
            if (num >= 10) {
                num = (num / 10) + (num % 10);
            }
        }

        sumaTotal += num;
        segundo = !segundo;
    }

    if (sumaTotal % 10 == 0) {
        ui->resultLabel->setText("¡Tarjeta válida!");
        ui->resultLabel->setStyleSheet("background-color: #86ff8e;");
    } else {
       ui->resultLabel->setStyleSheet("background-color: yellow;");
        ui->resultLabel->setText("¡Tarjeta inválida!");

}
}



void MainWindow::on_btn_convertir_clicked()
{

    int index = ui->comboBox_conversiones->currentIndex();
    QString ingreso = ui->lE_convertir->text();

    char l = ingreso[0].toLatin1();

    switch(index){

    //letra a binario
    case 0:{
        if (ingreso.isEmpty()) {
            QMessageBox::warning(this, "Error", "¡El campo de texto está vacío!");
            break;
        }
        QString binario;
        for (int i = 7; i >= 0; --i) {
            if (l & (1 << i)) {
                binario += '1';
            } else {
                binario += '0';
            }
        }
        qDebug() << "Binario:" << binario;
        ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
        ui->lbl_conversion->setText("Letra a Binario: " + binario);
        break;
    }
    //letra a decimal
    case 1:{
        if (ingreso.isEmpty()) {
            QMessageBox::warning(this, "Error", "¡El campo de texto está vacío!");
            break;
        }
        int i = l;
        ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
        ui->lbl_conversion->setText("Letra a Decimal: " + QString::number(i));
        break;
        }
    //letra a hexadecimal
    case 2:{
            if (ingreso.isEmpty()) {
                QMessageBox::warning(this, "Error", "¡El campo de texto está vacío!");
                break;
            }
            QString hexa = QString::number(l, 16).toUpper();
            ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
            ui->lbl_conversion->setText("Letra a Hexadecimal: " + hexa);
            break;
        }
    //binario a letra
    case 3:{
            if (ingreso.isEmpty()) {
                QMessageBox::warning(this, "Error", "¡El campo de texto está vacío!");
                break;
            }

            if (ingreso.length() != 8) {
                QMessageBox::warning(this, "Error", "¡Debe tener 8 bits!");
                break;
            }

            char letra = 0;
            for (int i = 0, j = 128; i < 8; i++, j /= 2) {
                if (ingreso[i] == '1') {
                    letra += j;
                }
            }
            ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
            ui->lbl_conversion->setText("Binario a Letra: " + QString(letra));
            break;
    }
    //Decimal a letra
    case 4:{
        if (ingreso.isEmpty()) {
            QMessageBox::warning(this, "Error", "¡El campo de texto está vacío!");
            break;
        }

        bool bien;
        int dec = ingreso.toInt(&bien);
        char letra2 = static_cast<char>(dec);
        ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
        ui->lbl_conversion->setText("Decimal a Letra: " + QString(letra2));
    }
        //hexadecimal a letra
    case 5:{
        bool esHexadecimal = ingreso.startsWith("0x") || ingreso.startsWith("0X") || ingreso.contains(QRegularExpression("^[0-9A-Fa-f]+$"));
        if (!esHexadecimal) {
            QMessageBox::warning(this, "Error", "¡Ingrese un número hexadecimal válido!");
            break;
        }
        bool bien;
        int hexValor = ingreso.toInt(&bien, 16); // Base 16 para hexadecimal


        if (hexValor < 0 || hexValor > 255) {
            QMessageBox::warning(this, "Error", "¡El número hexadecimal debe estar entre 0x00 y 0xFF!");
            break;
        }


        char letra = static_cast<char>(hexValor);
        ui->lbl_conversion->setStyleSheet("background-color: rgb(134, 255, 142)");
        ui->lbl_conversion->setText("Hexadecimal a Letra: " + QString(letra));
        break;
    }

    default:
        break;

    }
}


void MainWindow::on_comboBox_conversiones_activated(int index)
{
    if(index == 0 || index == 1 || index == 2){
        QRegularExpression regex("^[A-Za-z]$");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
        ui->lE_convertir->setValidator(validator);
    }else if(index == 3){
        QRegularExpression regExp("[01]+");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
        ui->lE_convertir->setValidator(validator);

    }
}

