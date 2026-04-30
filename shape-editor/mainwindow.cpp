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

    colorButton = new QToolButton();
    updateColorButton();
    connect(colorButton, &QToolButton::clicked, this, &MainWindow::chooseColor);

    // Добавляем в toolbar
    ui->toolBar->addWidget(colorButton);

}

MainWindow::~MainWindow()
{
    delete colorButton;
    delete paintbox;
    delete ui;
}


void MainWindow::on_actionChooseRectangleDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateRectangle);
    qDebug() << "actionChooseRectangleDraw";
}

void MainWindow::on_actionChooseEllipseDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateEllipse);
    qDebug() << "actionChooseEllipseDraw";
}

void MainWindow::on_actionChooseSquareDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateSquare);
    qDebug() << "actionChooseEllipseDraw";

}

void MainWindow::on_actionChooseCircleDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateCircle);
    qDebug() << "actionChooseCircleDraw";
}

void MainWindow::on_actionChooseLineDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateLine);
    qDebug() << "actionChooseLineDraw";
}

void MainWindow::on_actionSelectFillingColor_triggered()
{
    paintbox->setOperation(paintbox->Operations::FillShape);
    paintbox->fillSelectedShapes();
    qDebug() << "actionSelectFillingColor";
}

void MainWindow::on_actionSelect_triggered()
{
    paintbox->setOperation(paintbox->Operations::Operations);
    qDebug() << "actionSelect";
}

void MainWindow::chooseColor()
{
    QColor c = QColorDialog::getColor(paintbox->getColor(), this, "Цвет фигур");
    if (c.isValid()) paintbox->setColor(c);
    updateColorButton();
}

void MainWindow::updateColorButton()
{
    QPixmap pixmap(20, 20);
    pixmap.fill(paintbox->getColor());

    // рамка
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(0, 0, 19, 19);

    colorButton->setIcon(QIcon(pixmap));
}

void MainWindow::on_actionNew_triggered()
{
    paintbox->clearAll();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSelectAll_triggered()
{
    paintbox->selectAll();
}

void MainWindow::on_actionUnselectAll_triggered()
{
    paintbox->unselectAll();
}

void MainWindow::on_actionDeleteSelected_triggered()
{
    paintbox->deleteSelected();
}

void MainWindow::on_actionDeleteAll_triggered()
{
    paintbox->deleteAll();
}

void MainWindow::on_actionSelectLines_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Line);
}

void MainWindow::on_actionSelectRectagles_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Rect);
}

void MainWindow::on_actionSelectTriangles_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Triangle);
}

void MainWindow::on_actionSelectCircles_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Circle);
}

void MainWindow::on_actionSelectSquares_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Square);
}

void MainWindow::on_actionSelectEllipses_triggered()
{
    paintbox->selectByType(PaintBox::ShapeType::Ellipse);
}

void MainWindow::on_actionChooseTriangleDraw_triggered()
{
    paintbox->setOperation(paintbox->Operations::CreateTriangle);
    qDebug() << "actionChooseTriangleDraw";
}