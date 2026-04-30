#ifndef PAINTBOX_H
#define PAINTBOX_H

#include <QObject>
#include <QWidget>
#include "storage.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QResizeEvent>

#include <QMessageBox>

#include "shapes/shape.h"
#include "shapes/rect.h"
#include "shapes/ell.h"
#include "shapes/sqr.h"
#include "shapes/circ.h"
#include "shapes/line.h"
#include "shapes/triang.h"

class PaintBox: public QWidget
{
    Q_OBJECT

public:
    enum class Operations {
        Operations,
        FillShape,
        CreateLine,
        CreateTriangle,
        CreateRectangle,
        CreateEllipse,
        CreateSquare,
        CreateCircle
    };

    QColor getColor() const;
    void setColor(QColor);

private:
    bool multiSelect = false;

    Storage<Shape> storage;

    bool ctrl = false;
    bool leftMouse = false;
    QPoint lastMouseCoords;


    void unSelectAll(bool);
    void createNewShape();
    void fillShapes();
    void checkShapesContainsMouse(std::vector<Shape*>&);
    void clickToResizeSelected();

    Operations operation = Operations::Operations;

    QColor color = Qt::red;

    enum class States {
        States,
        Preview,
        Moving,
        Resizing
    };

    States state = States::States;
    Shape* stateShape = nullptr;

public:
    PaintBox(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void fillSelectedShapes();

    void setOperation(Operations);
    void selectAll();
    void unselectAll();
    void deleteSelected();
    void deleteAll();
    void clearAll();
    
    enum class ShapeType {
        Rect, Ellipse, Square, Circle, Line, Triangle
    };
    void selectByType(ShapeType type);
};

#endif // PAINTBOX_H
