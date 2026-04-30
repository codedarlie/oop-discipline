#ifndef PAINTBOX_H
#define PAINTBOX_H

#include <QObject>
#include <QWidget>
#include "storage.h"
#include "ccircle.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QResizeEvent>


#include <QMessageBox>

class PaintBox: public QWidget
{
    Q_OBJECT

private:
    Storage<CCircle> storage;

    bool ctrl = false;
public:
    PaintBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

};

#endif // PAINTBOX_H
