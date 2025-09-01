#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mymovableButton = new myMovableButton(this);
    mymovableButton->setText("Начать");
    mymovableButton->resize(90, 25);
    mymovableButton->move(100, 100);
    // mymovableButton->setCursor(Qt::OpenHandCursor);
    // mymovableButton->setEnabled(false);
    mymovableButton->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
