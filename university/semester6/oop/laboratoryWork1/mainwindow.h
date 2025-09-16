#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDate>
#include <QTime>
#include <QMessageBox>

#include "mymovablebutton.h"

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

private:
    // Main
    Ui::MainWindow *ui;

    // First Page
    myMovableButton *startButton;

    // Second Page
    // Progress Bar
    bool nameEmpty = true;
    bool ageEmpty = true;
    bool genderEmpty = true;
    void changeregistrationProgressBar(bool, bool&);
    void changeLabelHelperString(const QString&);

    QString name;

    // Third Page
    QDate minDate = QDate(2025, 1, 1);
    QTime minTime = QTime(0, 0);

    void mousePressEvent(QMouseEvent* event);

private slots:
    void switchToPage1();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_ageSpinBox_valueChanged(int arg1);
    void on_genderComboBox_currentIndexChanged(int index);
    void on_toRegistratePushButton_pressed();
    void on_dateHorizontalSlider_valueChanged(int value);
    void on_timeDial_valueChanged(int value);
    void on_dateTimePagePushButton_pressed();
    void on_pushButton_3_pressed();
    void on_horizontalScrollBar_valueChanged(int value);
    void on_radioButton_3_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_page3checkButton_clicked();
};
#endif // MAINWINDOW_H
