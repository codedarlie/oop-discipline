#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // Начальное меню

    setFixedSize(400, 400);

    // Настроки первой страницы
    QWidget* firstPage = ui->stackedWidget->widget(0);

    startButton = new myMovableButton(firstPage);
    startButton->setText("Начать");
    startButton->resize(90, 25);
    startButton->move(100, 100);
    startButton->setButtonPlaceCoords(ui->buttonPlace->x(), ui->buttonPlace->y());
    startButton->show();

    connect(startButton, &myMovableButton::switchToPage1, this, &MainWindow::switchToPage1);

    // Настройки второй страницы
    QStringList comboboxList = {"М", "Ж", "Не скажу"};
    ui->genderComboBox->addItems(comboboxList);
    ui->ageSpinBox->setMaximum(150);
    ui->nameLineEdit->setMaxLength(25);
    ui->labelHelper->setVisible(false);

    // Настройки третьей страницы

    // Настройки четвертой страницы
    ui->binLcdNumber->display(rand() % 1024);

    int start = 5000;
    int end = 9999;
    int randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton_2->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;
    ui->radioButton_3->setText(QString::number(randNum));
    randNum = (rand() % (end - start + 1)) + start;

    ui->octLcdNumber->display(randNum);
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

    // Настройки пятой страницы
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeOut);

    // Настройки шестой страницы
    // sizes = std::array<std::pair<int, int>, 6> (
        // {314, 634},
        // {1000, 500},
        // {300, 200},
        // {754, 321},
        // {1, 1},
        // {1300, 650} );
}

void MainWindow::switchToPage1() {
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::changeregistrationProgressBar(bool add, bool& empty) {
    int value = ui->registrationProgressBar->value();
    if (!add) {
        if (value <= 1) ui->registrationProgressBar->setValue(0);
        else ui->registrationProgressBar->setValue(value - 1);
        empty = true;
    } else if (empty) {
        ui->registrationProgressBar->setValue(value + 1);
        empty = false;
    }

    if (ui->registrationProgressBar->value() == ui->registrationProgressBar->maximum()) {
        ui->toRegistratePushButton->setEnabled(true);
    } else {
        ui->toRegistratePushButton->setEnabled(false);
    }
}

void MainWindow::changeLabelHelperString(const QString &label)
{
    ui->labelHelper->setText(label);
}

// todo: переделать координаты widget - что в первой странице, что здесь криво показывает

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 4) {
        QRect r = ui->widget->geometry();
        QPoint mouse = event->pos();
        if ((r.x() <= mouse.x()) && (mouse.x() <= r.x() + r.width()) && (r.y() <= mouse.y()) && (mouse.y() <= r.y() + r.height())) {
            if (event->button() == Qt::RightButton) {
                ui->stackedWidget->setCurrentIndex(5);
                pageFiveRestart();
            } else {
                QMessageBox::warning(this, "Уведомление", "Нажали не ту кнопку!");
            }
        } else {
            QMessageBox::warning(this, "Уведомление", "Нажали вне окна!");
        }
        // qDebug() << mouse.x() << " and " << mouse.y();
        // qDebug() << r.x() << " | " << r.width() << " and " << r.y() << " | " << r.height();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 5) {
        if (event->text() == "") return;
        // qDebug() << "Key: " << event->text();
        QString key = event->text();
        QString pasteTextBrowser = ui->page5PasteTextBrowser->toPlainText() + key;
        QString copyTextBrowser = ui->page5CopyTextBrowser->toPlainText();

        ui->page5PasteTextBrowser->setText(pasteTextBrowser);

        // qDebug() << "copyTextBrowser: " << copyTextBrowser << "\now pasteTextBrowser" << pasteTextBrowser;

        if (copyTextBrowser.size() >= pasteTextBrowser.size()) {
            if (copyTextBrowser[pasteTextBrowser.size() - 1] == key) {
                if (copyTextBrowser == pasteTextBrowser) {
                    timer->stop();
                    ui->stackedWidget->setCurrentIndex(6);
                    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
                    setMinimumSize(1, 1);
                }
            } else {
                QMessageBox::warning(this, "Уведомление" , "Нажали не ту кнопку!");
                pageFiveRestart();
                ui->page5PasteTextBrowser->setText("");
            }
        } else {
            QMessageBox::warning(this, "Уведомление" , "Символов справа стало больше!!!");
            pageFiveRestart();
            ui->page5PasteTextBrowser->setText("");
        }
    }
}

void MainWindow::pageFiveRestart()
{
    qDebug() << "pageFiveRestart";
    timeCounter = 59;
    ui->page5Timer->setTime(QTime(0, 0, timeCounter));
    generateRandomWord();
    timer->setInterval(1000);
    timer->start();
}

void MainWindow::generateRandomWord()
{
    qDebug() << "generateRandomWord";
    ui->page5CopyTextBrowser->setText("");
    for (int i = 0; i < 1; ++i) {
        char r = 'a' + (rand() % 26);
        QString s = ui->page5CopyTextBrowser->toPlainText() + r;
        ui->page5CopyTextBrowser->setText(s);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 6) {
        int currentWidth = event->size().width();
        int currentHeight = event->size().height();
        ui->page6CurrentWIndowSize->setText("Текущий размер окна: " + QString::number(currentWidth) + "x" + QString::number(currentHeight));
        qDebug() << currentWidth << " " << currentHeight;

        // if ()
    }
}

void MainWindow::timeOut()
{
    --timeCounter;
    ui->page5Timer->setTime(QTime(0, 0, timeCounter));
    if (!timeCounter) {
        QMessageBox::warning(this, "Уведомление", "Время вышло, попробуй еще раз!");
        pageFiveRestart();
    } else {
        timer->setInterval(1000);
        timer->start();
    }
}

void MainWindow::on_nameLineEdit_textChanged(const QString &arg1)
{
    changeLabelHelperString(QString::number(arg1.size()) + " / 25");
    changeregistrationProgressBar(arg1.size(), nameEmpty);

    if (arg1.size() > 10) {
        ui->labelHelper->setVisible(true);
    } else {
        ui->labelHelper->setVisible(false);
    }

    name = ui->nameLineEdit->text();

    ui->page2Label->setText("Добро пожаловать, \n" + name + "!");
}

void MainWindow::on_ageSpinBox_valueChanged(int arg1)
{
    changeLabelHelperString(QString::number(arg1) + " / 150");
    changeregistrationProgressBar(arg1, ageEmpty);

    if (arg1 > 15) {
        ui->labelHelper->setVisible(true);
    } else {
        ui->labelHelper->setVisible(false);
    }
}


void MainWindow::on_genderComboBox_currentIndexChanged(int index)
{
    ui->labelHelper->setVisible(false);
    if (index != -1) {
        changeregistrationProgressBar(true, genderEmpty);
    }
}

void MainWindow::on_toRegistratePushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_dateHorizontalSlider_valueChanged(int value)
{
    QDate newDate = minDate.addDays(value);
    ui->dateEdit->setDate(newDate);
}

void MainWindow::on_timeDial_valueChanged(int value)
{
    QTime newTime = minTime.addSecs(value);
    ui->timeEdit->setTime(newTime);
}

void MainWindow::on_dateTimePagePushButton_pressed()
{
    if (ui->timeEdit->time().hour() == QTime::currentTime().hour() &&
        ui->timeEdit->time().minute() == QTime::currentTime().minute() &&
        ui->dateEdit->date() == QDate::currentDate()) {
        ui->stackedWidget->setCurrentIndex(3);
    } else {
        QMessageBox::warning(this, "Результат", "Не получилось, попробуй еще раз!");

        int randDate = rand() % ui->dateHorizontalSlider->maximum();
        ui->dateHorizontalSlider->setValue(randDate);
        on_dateHorizontalSlider_valueChanged(randDate);

        int randTime = rand() % ui->timeDial->maximum();
        ui->timeDial->setValue(randTime);
        on_timeDial_valueChanged(randTime);
    }
}

void MainWindow::on_pushButton_3_pressed()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->decLcdNumber1->display(ui->horizontalScrollBar->value());
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->decLcdNumber2->display(ui->radioButton_3->text().toInt());
}


void MainWindow::on_radioButton_clicked()
{
    ui->decLcdNumber2->display(ui->radioButton->text().toInt());
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->decLcdNumber2->display(ui->radioButton_2->text().toInt());
}


void MainWindow::on_page3checkButton_clicked()
{
    int dec1 = ui->decLcdNumber1->intValue();
    int bin = ui->binLcdNumber->intValue();

    int dec2 = ui->decLcdNumber2->intValue();
    int oct = ui->octLcdNumber->intValue();

    qDebug() << dec1 << "==" << bin << " | " << dec2 << "==" << oct;
    if (dec1 == bin && dec2 == oct) {
        ui->stackedWidget->setCurrentIndex(4);
    } else {
        QMessageBox::warning(this, "Уведомление", "Вы неправильно перевели числа!");
    }
}

