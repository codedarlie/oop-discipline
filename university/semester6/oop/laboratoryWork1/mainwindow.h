#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mymovablebutton.h"

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

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
    // void mouseMoveEvent(QMouseEvent* event);
    void warningMessageBox(QString);

    // Main
    Ui::MainWindow *ui;

    // Page 0
    myMovableButton *startButton;
    void page0SingleShot();

    // Page 1
    bool nameEmpty = true;
    bool ageEmpty = true;
    bool genderEmpty = true;
    void changeRegProgress(bool, bool&);
    void changeLabelHelper(const QString&);
    QString name;

    // Page 2
    QDate minDate = QDate(2025, 1, 1);
    QTime minTime = QTime(0, 0);

    // Page 3
    void mousePressEvent(QMouseEvent* event);

    // Page 4    
    QTimer *timer;
    int timeCounter;
    void page5Restart();
    void generateRandomWord();
    void keyPressEvent(QKeyEvent* event);

    // Page 5;
    int curSizeIndex {-1};

    std::array<std::pair<int, int>, 3> sizesChallenge = {{
        {1300, 650},
        {10, 10},
        {300, 200},
    }};

    void page6Settings();
    void setNextWindowSize();
    void resizeEvent(QResizeEvent* event);

private slots:
    // Skip Button
    void on_skipButton_pressed();

    // Page 1
    void page1Settings();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_ageSpinBox_valueChanged(int arg1);
    void on_genderComboBox_currentIndexChanged(int index);
    void on_regButton_clicked();

    // Page 2
    void on_dateSlider_valueChanged(int value);
    void on_timeDial_valueChanged(int value);
    void on_dateTimeButton_pressed();

    // Page 3
    void on_decScrollBar_valueChanged(int value);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_numButton_clicked();

    // Page 5
    void timeOut();


};
#endif // MAINWINDOW_H
