#ifndef MYMOVABLEBUTTON_H
#define MYMOVABLEBUTTON_H


#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>

class myMovableButton : public QPushButton
{
    Q_OBJECT

public:
    explicit myMovableButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void checkPosition();
private:
    bool fellIntoPlace;

    bool dragging;
    QPoint dragPosition;
};

#endif // MYMOVABLEBUTTON_H
