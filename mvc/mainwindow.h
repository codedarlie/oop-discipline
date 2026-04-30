#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "model.h"
#include "abc.h"

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateData(int a, int b, int c);

private slots:
    // void on_lineEditA_textChanged(const QString &arg1);
    // void on_lineEditB_textChanged(const QString &arg1);
    // void on_lineEditC_textChanged(const QString &arg1);

    // void on_spinBoxA_valueChanged(int arg1);
    // void on_spinBoxB_valueChanged(int arg1);
    // void on_spinBoxC_valueChanged(int arg1);

    void on_horizontalSliderA_valueChanged(int value);
    void on_horizontalSliderB_valueChanged(int value);
    void on_horizontalSliderC_valueChanged(int value);

    // void updateData(int, int, int);

    void on_spinBoxA_editingFinished();
    void on_spinBoxB_editingFinished();
    void on_spinBoxC_editingFinished();

    void on_lineEditA_editingFinished();
    void on_lineEditB_editingFinished();
    void on_lineEditC_editingFinished();

private:
    Ui::MainWindow *ui;
    controller* c;
    model* m;

    bool updating {false};

signals:
    void sendValueToController(abc, int);
    void initializeSignal();
};

#endif // MAINWINDOW_H
