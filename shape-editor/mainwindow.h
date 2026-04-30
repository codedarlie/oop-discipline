#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintbox.h"

#include <QMainWindow>
#include <QPainter>
#include <QToolButton>
#include <QColorDialog>

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
    void on_actionChooseRectangleDraw_triggered();
    void on_actionChooseEllipseDraw_triggered();
    void on_actionChooseSquareDraw_triggered();
    void on_actionChooseCircleDraw_triggered();
    void on_actionChooseLineDraw_triggered();
    void on_actionSelectFillingColor_triggered();
    void on_actionSelect_triggered();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionSelectAll_triggered();
    void on_actionUnselectAll_triggered();
    void on_actionDeleteSelected_triggered();
    void on_actionDeleteAll_triggered();
    void on_actionSelectLines_triggered();
    void on_actionSelectRectagles_triggered();
    void on_actionSelectTriangles_triggered();
    void on_actionSelectCircles_triggered();
    void on_actionSelectSquares_triggered();
    void on_actionSelectEllipses_triggered();
    void on_actionChooseTriangleDraw_triggered();


    void chooseColor();
private:
    Ui::MainWindow *ui;

    PaintBox* paintbox;

    QToolButton* colorButton;

    void updateColorButton();
};
#endif // MAINWINDOW_H
