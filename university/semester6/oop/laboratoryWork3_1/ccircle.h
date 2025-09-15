#ifndef CCIRCLE_H
#define CCIRCLE_H

#include <QDebug>
#include <QPainter>

#include <tuple>

class CCircle
{
private:
    int x;
    int y;
    const double radius = 20;
    bool selected = false;
    bool hovered = false;
    bool hide = false;

public:
    CCircle(int, int);

    bool containsPoint(int, int) const;
    void draw(QPainter&) const;

    void setSelected(bool);
    void setHovered(bool);
    void setHide(bool);

    const std::tuple<int, int, double, bool, bool> getInfo() const;
    int getX() const;
    int getY() const;
    double getRadius() const;
    bool getSelected() const;
    bool getHovered() const;
    ~CCircle();
};

#endif // CCIRCLE_H
