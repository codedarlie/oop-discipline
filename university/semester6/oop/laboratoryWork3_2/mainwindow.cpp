#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m(new model())
{
    c = new controller(m);

    ui->setupUi(this);

    ui->lineEditA->setValidator(new QIntValidator(this));
    ui->lineEditB->setValidator(new QIntValidator(this));
    ui->lineEditC->setValidator(new QIntValidator(this));

    connect(this, &MainWindow::sendValueToController, c, &controller::receiveValue);

    connect(m, &model::updateView, this, &MainWindow::updateData);

    connect(this, &MainWindow::initializeSignal, c, &controller::initializeSlot);
    emit initializeSignal();

}

MainWindow::~MainWindow()
{
    delete m;
    delete c;
    delete ui;
}

void MainWindow::on_lineEditA_editingFinished()
{
    sendValueToController(abc::A, ui->lineEditA->text().toInt());
}
void MainWindow::on_lineEditB_editingFinished()
{
    sendValueToController(abc::B, ui->lineEditB->text().toInt());
}
void MainWindow::on_lineEditC_editingFinished()
{
    sendValueToController(abc::C, ui->lineEditC->text().toInt());
}

// void MainWindow::on_lineEditA_textChanged(const QString &arg1)
// {
//     qDebug() << "le1: " << arg1;
//     // lineEditTextChanged(abc::A, arg1);
//     sendValueToController(abc::A, arg1.toInt());
// }

// void MainWindow::on_lineEditB_textChanged(const QString &arg1)
// {
//     qDebug() << "le2: " << arg1;
//     // lineEditTextChanged(abc::B, arg1);
//     sendValueToController(abc::B, arg1.toInt());
// }

// void MainWindow::on_lineEditC_textChanged(const QString &arg1)
// {
//     qDebug() << "le3: " << arg1;
//     // lineEditTextChanged(abc::C, arg1);
//     sendValueToController(abc::C, arg1.toInt());
// }

void MainWindow::on_spinBoxA_editingFinished()
{
    sendValueToController(abc::A, ui->spinBoxA->value());
}
void MainWindow::on_spinBoxB_editingFinished()
{
    sendValueToController(abc::B, ui->spinBoxB->value());
}
void MainWindow::on_spinBoxC_editingFinished()
{
    sendValueToController(abc::C, ui->spinBoxC->value());
}

// void MainWindow::on_spinBoxA_valueChanged(int arg1)
// {
//     qDebug() << "sb1: " << QString::number(arg1);
//     // spinBoxValueChanged(abc::A, arg1);
//     sendValueToController(abc::A, arg1);
// }

// void MainWindow::on_spinBoxB_valueChanged(int arg1)
// {
//     qDebug() << "sb2: " << QString::number(arg1);
//     // spinBoxValueChanged(abc::B, arg1);
//     sendValueToController(abc::B, arg1);
// }

// void MainWindow::on_spinBoxC_valueChanged(int arg1)
// {
//     qDebug() << "sb3: " << QString::number(arg1);
//     sendValueToController(abc::C, arg1);
//     // spinBoxValueChanged(abc::C, arg1);
// }

// void MainWindow::horizontalSliderValueChanged(int value)
// { }

void MainWindow::on_horizontalSliderA_valueChanged(int value)
{
    // qDebug() << "hs1: " << QString::number(value);
    sendValueToController(abc::A, value);
}
void MainWindow::on_horizontalSliderB_valueChanged(int value)
{
    // qDebug() << "hs2: " << QString::number(value);
    sendValueToController(abc::B, value);
}
void MainWindow::on_horizontalSliderC_valueChanged(int value)
{
    // qDebug() << "hs3: " << QString::number(value);
    sendValueToController(abc::C, value);
}

void MainWindow::updateData(int a, int b, int c)
{
    if (updating) return;

    updating = true;

    ui->lineEditA->setText(QString::number(a));
    ui->lineEditB->setText(QString::number(b));
    ui->lineEditC->setText(QString::number(c));

    ui->spinBoxA->setValue(a);
    ui->spinBoxB->setValue(b);
    ui->spinBoxC->setValue(c);

    ui->horizontalSliderA->setValue(a);
    ui->horizontalSliderB->setValue(b);
    ui->horizontalSliderC->setValue(c);

    updating = false;
}

