#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Настройки страницы
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // SKIP BUTTON
    ui->skipButton->setVisible(true);

    // Page 0
    QWidget* page0 = ui->stackedWidget->widget(0);

    startButton = new myMovableButton(page0);
    startButton->setText("Начать");
    startButton->resize(90, 25);
    startButton->show();

    connect(startButton, &myMovableButton::switchToPage1, this, &MainWindow::page1Settings);

    QTimer::singleShot(0, this, &MainWindow::page0SingleShot);

    // Page 1
    QStringList comboboxList = {"Не скажу", "М", "Ж", "Другое"};
    ui->genderComboBox->addItems(comboboxList);
    ui->ageSpinBox->setMaximum(150);
    ui->nameLineEdit->setMaxLength(25);
    ui->labelHelper->setVisible(false);

    // Page 3
    ui->binLcd->display(rand() % 1024);

    int start = 5000;
    int end = 9999;

    int randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton_2->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton_3->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;
    ui->octLcd->display(randNum);

    int randi = rand() % 3;

    switch(randi) {
    case 0:
        ui->radioButton->setText(QString::number(randNum));
        break;
    case 1:
        ui->radioButton_2->setText(QString::number(randNum));
        break;
    default:
        ui->radioButton_3->setText(QString::number(randNum));
    }

    // Page 5
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeOut);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

// void MainWindow::mouseMoveEvent(QMouseEvent *event)
// {
//     QPoint mouse = event->pos();
//     qDebug() << mouse.x() << " and " << mouse.y();
// }


// Skip button
void MainWindow::on_skipButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    if (ui->stackedWidget->currentIndex() == 5) {
        page5Restart();
    } else if (ui->stackedWidget->currentIndex() == 6) {
        page6Settings();
    }
}

// Page 0
void MainWindow::page0SingleShot()
{
    startButton->move(ui->buttonPlace->x(), 20);
    startButton->setButtonPlaceCoords(ui->buttonPlace->x(), ui->buttonPlace->y());
}

// Page 1
void MainWindow::page1Settings() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_nameLineEdit_textChanged(const QString &arg1)
{
    changeLabelHelper(QString::number(arg1.size()) + " / 25");
    changeRegProgress(arg1.size(), nameEmpty);

    if (arg1.size() > 10) {
        ui->labelHelper->setVisible(true);
    } else {
        ui->labelHelper->setVisible(false);
    }

    name = ui->nameLineEdit->text();

    ui->welcomingLabel->setText("Добро пожаловать, \n" + name + "!");
}

void MainWindow::on_ageSpinBox_valueChanged(int arg1)
{
    changeLabelHelper(QString::number(arg1) + " / 150");
    changeRegProgress(arg1, ageEmpty);

    if (arg1 > 8) {
        ui->labelHelper->setVisible(true);
    } else {
        ui->labelHelper->setVisible(false);
    }
}

void MainWindow::on_genderComboBox_currentIndexChanged(int index)
{
    ui->labelHelper->setVisible(false);
    if (index == 1 || index == 2 || index == 3) {
        changeRegProgress(true, genderEmpty);
    } else {
        changeRegProgress(false, genderEmpty);
    }
}

void MainWindow::on_regButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::changeRegProgress(bool add, bool& empty) {
    int value = ui->regProgressBar->value();
    if (!add) {
        if (value <= 1) ui->regProgressBar->setValue(0);
        else ui->regProgressBar->setValue(value - 1);
        empty = true;
    } else if (empty) {
        ui->regProgressBar->setValue(value + 1);
        empty = false;
    }

    if (ui->regProgressBar->value() == ui->regProgressBar->maximum()) {
        ui->regButton->setEnabled(true);
    } else {
        ui->regButton->setEnabled(false);
    }
}

void MainWindow::changeLabelHelper(const QString &label)
{
    ui->labelHelper->setText(label);
}


// Page 2
void MainWindow::on_dateSlider_valueChanged(int value)
{
    QDate newDate = minDate.addDays(value);
    ui->dateEdit->setDate(newDate);
}

void MainWindow::on_timeDial_valueChanged(int value)
{
    QTime newTime = minTime.addSecs(value);
    ui->timeEdit->setTime(newTime);
}

void MainWindow::on_dateTimeButton_pressed()
{
    if (ui->timeEdit->time().hour() == QTime::currentTime().hour() &&
        ui->timeEdit->time().minute() == QTime::currentTime().minute() &&
        ui->dateEdit->date() == QDate::currentDate()) {
        ui->stackedWidget->setCurrentIndex(3);
    } else {
        warningMessageBox("Не получилось, попробуй еще раз!");

        int randDate = rand() % ui->dateSlider->maximum();
        ui->dateSlider->setValue(randDate);
        on_dateSlider_valueChanged(randDate);

        int randTime = rand() % ui->timeDial->maximum();
        ui->timeDial->setValue(randTime);
        on_timeDial_valueChanged(randTime);
    }
}


// Page 3
void MainWindow::on_decScrollBar_valueChanged(int value)
{
    ui->decLcd1->display(value);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->decLcd2->display(ui->radioButton_3->text().toInt());
}

void MainWindow::on_radioButton_clicked()
{
    ui->decLcd2->display(ui->radioButton->text().toInt());
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->decLcd2->display(ui->radioButton_2->text().toInt());
}

void MainWindow::on_numButton_clicked()
{
    int dec1 = ui->decLcd1->intValue();
    int bin = ui->binLcd->intValue();

    int dec2 = ui->decLcd2->intValue();
    int oct = ui->octLcd->intValue();

    qDebug() << "Dec: " << dec1 << "\nBin: " << bin << "\nDec: " << dec2 << "\nOct: " << oct;
    if (dec1 == bin && dec2 == oct) {
        ui->stackedWidget->setCurrentIndex(4);
    } else {
        warningMessageBox("Вы неправильно перевели числа!");
    }
}


// Page 4
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 4) {
        QRect r = ui->clickWidget->geometry();
        QPoint mouse = event->pos();
        int widgetX = r.x() + ui->stackedWidget->x();
        int widgetY = r.y() + ui->stackedWidget->y();
        int widgetX2 = widgetX + r.width();
        int widgetY2 = widgetY + r.height();

        if ((widgetX <= mouse.x()) && (mouse.x() <= widgetX2) && (widgetY <= mouse.y()) && (mouse.y() <= widgetY2)) {
            if (event->button() == Qt::RightButton) {
                ui->stackedWidget->setCurrentIndex(5);
                page5Restart();
            } else {
                warningMessageBox("Нажали не ту кнопку!");
            }
        } else {
            warningMessageBox("Нажали вне окна!");
        }
    }
}


// Page 5
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 5) {
        if (event->text() == "") return;
        QString key = event->text();
        QString pasteText = ui->pasteText->toPlainText() + key;
        QString copyText = ui->copyText->toPlainText();

        ui->pasteText->setText(pasteText);

        if (copyText.size() >= pasteText.size()) {
            if (copyText[pasteText.size() - 1] == key) {
                if (copyText == pasteText) {
                    page6Settings();
                }
            } else {
                warningMessageBox("Нажали не ту кнопку!");
                page5Restart();
                ui->pasteText->setText("");
            }
        } else {
            warningMessageBox("Символов справа стало больше!!!");
            page5Restart();
            ui->pasteText->setText("");
        }
    }
}

void MainWindow::timeOut()
{
    --timeCounter;
    ui->timer->setTime(QTime(0, 0, timeCounter));
    if (!timeCounter) {
        warningMessageBox("Время вышло, попробуй еще раз!");
        page5Restart();
    } else {
        timer->setInterval(1000);
        timer->start();
    }
}

void MainWindow::page5Restart()
{
    timeCounter = 30;
    ui->timer->setTime(QTime(0, 0, timeCounter));
    generateRandomWord();
    timer->setInterval(1000);
    timer->start();
}

void MainWindow::generateRandomWord()
{
    ui->copyText->setText("");
    for (int i = 0; i < 15; ++i) {
        char r = 'a' + (rand() % 26);
        QString s = ui->copyText->toPlainText() + r;
        ui->copyText->setText(s);
    }
}

// Page 6
void MainWindow::page6Settings()
{
    timer->stop();
    ui->stackedWidget->setCurrentIndex(6);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setMinimumSize(10, 10);
    setNextWindowSize();
}

void MainWindow::setNextWindowSize()
{
    ++curSizeIndex;

    if (curSizeIndex == sizesChallenge.size()) {
        ui->stackedWidget->setCurrentIndex(7);
        return;
    }

    int nextWidth = sizesChallenge[curSizeIndex].first;
    int nextHeight = sizesChallenge[curSizeIndex].second;
    ui->nextSizeLabel->setText(QString::number(nextWidth) + "x" + QString::number(nextHeight));

    ui->curSizeLabel->setText("Текущий размер окна: " + QString::number(width()) + "x" + QString::number(height()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 0) {
        if (!startButton->getTouched()) {
            startButton->move(ui->buttonPlace->x(), 20);
        }
        startButton->setButtonPlaceCoords(ui->buttonPlace->x(), ui->buttonPlace->y());
    }

    else if (ui->stackedWidget->currentIndex() == 6) {
        int currentWidth = event->size().width();
        int currentHeight = event->size().height();
        ui->curSizeLabel->setText("Текущий размер окна: " + QString::number(currentWidth) + "x" + QString::number(currentHeight));

        int nextWidth = sizesChallenge[curSizeIndex].first;
        int nextHeight = sizesChallenge[curSizeIndex].second;

        if (currentWidth == nextWidth && currentHeight == nextHeight) {
            setNextWindowSize();
        }
    }
}

void MainWindow::warningMessageBox(QString s)
{
    QMessageBox::warning(this, "Уведомление", s);

    int rr = 70 + rand() % 80;
    int rg = 65 + rand() % 75;
    int rb = 80 + rand() % 85;

    setStyleSheet("background-color: rgb(" + QString::number(rr) + ", " + QString::number(rg) + ", " + QString::number(rb) + ")");
}
