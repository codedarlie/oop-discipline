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
    void setButtonPlaceCoords(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void checkPosition();
private:
    bool fellIntoPlace;

    bool dragging;
    QPoint dragPosition;

    std::pair<int, int> buttonPlaceCoords;

signals:
    void switchToPage1();
};

#endif // MYMOVABLEBUTTON_H
