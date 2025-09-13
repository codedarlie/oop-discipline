#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "abc.h"

// class MainWindow;
// void MainWindow::updateData(int, int, int);

class model: public QObject
{
    Q_OBJECT
public:
    // model(MainWindow* v, QObject* parent = nullptr);
    model(QObject* parent = nullptr);

    virtual ~model() {}

    // void setView(MainWindow* v);

private:
    int a;
    int b;
    int c;

    // MainWindow* view = nullptr;

public slots:
    void changeData(abc, int);
    void initializeSlot();

signals:
    void updateView(int, int, int);
};

#endif // MODEL_H
