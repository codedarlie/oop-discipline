#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , paintbox(new PaintBox(this))
{
    ui->setupUi(this);

    setCentralWidget(paintbox);

    paintbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete paintbox;
    delete ui;
}
