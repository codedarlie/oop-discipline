#include "paintbox.h"

PaintBox::PaintBox(QWidget *parent):
    QWidget(parent),
    storage(Storage<Shape>())
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    QPoint p1 (300, 200);
    QSize s1 (70, 80);
    Shape* r = new Rect(p1, s1);
    storage.append(r);

}

void PaintBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    for (int i = 0; i < storage.getSize(); ++i) storage.at(i)->draw(painter);

    if (state == States::Preview) stateShape->draw(painter);
}

void PaintBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) ctrl = true;

    if (event->key() == Qt::Key_Delete) {
        for (int i = storage.getSize() - 1; i >= 0 ; --i) {
            if (storage.at(i)->isSelected()) storage.remove(i);
        }
    }

    update();
}

void PaintBox::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) ctrl = false;
}

void PaintBox::resizeEvent(QResizeEvent *event)
{
    // QRect bounds ({0, 0}, event->size());
    // for (int i = 0; i < storage.getSize(); ++i) {
        // Shape* c = storage.at(i);
        // c->setHide(!c->isWithinBounds(bounds));
    // }

    QWidget::resizeEvent(event);

    update();
}

void PaintBox::mousePressEvent(QMouseEvent *event)
{
    lastMouseCoords = event->pos();

    if (event->button() == Qt::LeftButton) {
        /*
            на этот момент может быть что то выбранное

            с какой целью может быть нажато:
                + создание фигуры
                - выбрать фигуру / фигуры (убрать выбор если по пустому полю нажать)
                - покраска фигуры / фигур
        */

        clickToResizeSelected();
        if (state == States::Resizing) return;

        std::vector<Shape*> shapesContainsMouse {std::vector<Shape*>()};
        checkShapesContainsMouse(shapesContainsMouse);
        qDebug() << "shapesContainsMouse.size() " << QString::number(shapesContainsMouse.size());

        if (shapesContainsMouse.size()) {
            if (!ctrl) unSelectAll(false); // unSelectAll
            for (auto* sh: shapesContainsMouse) {
                sh->setSelected(true);
                sh->setMoving(true);
            }
            state = States::Moving;
            return;
        }

        bool isCreating = (operation == Operations::CreateRectangle ||
                           operation == Operations::CreateEllipse ||
                           operation == Operations::CreateSquare ||
                           operation == Operations::CreateCircle ||
                           operation == Operations::CreateLine ||
                           operation == Operations::CreateTriangle);
        
        if (isCreating) {
            int margin = 20; // минимальное расстояние от границы
            if (lastMouseCoords.x() < margin || lastMouseCoords.x() > width() - margin ||
                lastMouseCoords.y() < margin || lastMouseCoords.y() > height() - margin) {
                QMessageBox::warning(this, "Предупреждение", "Нельзя создавать фигуры у границы!");
                return;
            }
        }

        switch(operation) {
            case Operations::CreateRectangle:
            case Operations::CreateEllipse:
            case Operations::CreateSquare:
            case Operations::CreateCircle:
            case Operations::CreateLine:
            case Operations::CreateTriangle:
                createNewShape();
                break;
            case Operations::FillShape:
                qDebug() << "fillShape1";
                fillShapes();
                break;
            case Operations::Operations:
                qDebug() << "Operations::Operations";
                break;
        }
        update();
    }
}

void PaintBox::createNewShape() {
    unSelectAll(false);

    switch (operation) {
        case Operations::CreateEllipse:
            stateShape = new Ell(lastMouseCoords, QSize(0, 0));
            break;
        case Operations::CreateRectangle:
            stateShape = new Rect(lastMouseCoords, QSize(0, 0));
            break;
        case Operations::CreateSquare:
            stateShape = new Sqr(lastMouseCoords, 0);
            break;
        case Operations::CreateCircle:
            stateShape = new Circ(lastMouseCoords, 0);
            break;
        case Operations::CreateLine:
            stateShape = new Line(lastMouseCoords, QSize(0, 0));
            break;
        case Operations::CreateTriangle:
            stateShape = new Triang(lastMouseCoords, QSize(0, 0));
            break;
        default:
            throw std::logic_error("Не может быть не выбрана фигура.");
    }

    QColor c = color;
    c.setAlpha(100);
    stateShape->setColor(c);
    stateShape->setSelected(true);
    stateShape->setResizing(true);

    state = States::Preview;

    if (!stateShape->findHandles(lastMouseCoords)) {
        throw std::logic_error("У preview не может не быть handle.");
    } else {
        // изменить мышку
    }

}

void PaintBox::fillShapes()
{
    bool hitShape = false;
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        if (sh->containsPoint(lastMouseCoords)) {
            sh->setColor(color);
            hitShape = true;
        }
    }
    if (!hitShape) {
        operation = Operations::Operations;
    }
}

void PaintBox::fillSelectedShapes()
{
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        if (sh->isSelected()) {
            sh->setColor(color);
        }
    }
}

void PaintBox::checkShapesContainsMouse(std::vector<Shape*>& shapesContainsMouse)
{
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        if (sh->containsPoint(lastMouseCoords)) {
            if (!multiSelect) shapesContainsMouse.clear();
            shapesContainsMouse.push_back(sh);
        }
    }
}

void PaintBox::clickToResizeSelected()
{
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        if (sh->isSelected()) {
            if (sh->findHandles(lastMouseCoords)) {
                unSelectAll(false);
                sh->setSelected(true);
                sh->setResizing(true);
                state = States::Resizing;
                stateShape = sh;
                return;
            }
        }
    }
}

QColor PaintBox::getColor() const
{
    return color;
}

void PaintBox::setColor(QColor c)
{
    color = c;
}

void PaintBox::unSelectAll(bool v)
{
    for (int i = 0; i < storage.getSize(); ++i) {
        auto* sh = storage.at(i);
        sh->setSelected(v);
    }
}

void PaintBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentMouseCoords (event->pos());
    QSize bounds = size();
    QPoint offset = currentMouseCoords - lastMouseCoords;

    lastMouseCoords = currentMouseCoords;

    switch (state) {
        case States::States:
            break;
        case States::Preview:
        case States::Resizing:
            // stateShape->resize(currentMouseCoords, bounds);
            stateShape->resize(offset, bounds);
            break;
        case States::Moving:
            for (int i = 0; i < storage.getSize(); ++i) {
                auto* sh = storage.at(i);
                if (sh->getMoving()) {
                    sh->move(offset, bounds);
                }
            }
            break;
    }

    // Hovering
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        if (sh->containsPoint(currentMouseCoords)) sh->setHovered(true);
        else sh->setHovered(false);
    }

    update();
}

void PaintBox::mouseReleaseEvent(QMouseEvent *event)
{
    switch (state) {
        case States::Preview:
            if (stateShape->isShapeSmall()) {
                // QMessageBox::warning(this, "Уведомление", "Фигура слишком маленького размера!");
                delete stateShape;
                break;
            }
            stateShape->setColor(QColor(stateShape->getColor().red(), stateShape->getColor().green(), stateShape->getColor().blue(), 255));
            // stateShape->setSelected(false);
            stateShape->resizeEnd();
            stateShape->setResizing(false);
            storage.append(stateShape);
            stateShape = nullptr;
            break;
        case States::Moving:
            for (int i = 0; i < storage.getSize(); ++i) {
                storage.at(i)->setMoving(false);
            }
            break;
        case States::Resizing:
            stateShape->resizeEnd();
            stateShape->setResizing(false);
            stateShape = nullptr;
            break;
    }
    state = States::States;

    update();
}

void PaintBox::setOperation(Operations op)
{
    qDebug() << "Operations::FillShape";
    operation = op;
}


void PaintBox::selectAll()
{
    for (int i = 0; i < storage.getSize(); ++i) {
        storage.at(i)->setSelected(true);
    }
    update();
}

void PaintBox::unselectAll()
{
    for (int i = 0; i < storage.getSize(); ++i) {
        storage.at(i)->setSelected(false);
    }
    update();
}

void PaintBox::deleteSelected()
{
    for (int i = storage.getSize() - 1; i >= 0; --i) {
        if (storage.at(i)->isSelected()) {
            storage.remove(i);
        }
    }
    update();
}

void PaintBox::deleteAll()
{
    for (int i = storage.getSize() - 1; i >= 0; --i) {
        storage.remove(i);
    }
    update();
}

void PaintBox::clearAll()
{
    deleteAll();
}

void PaintBox::selectByType(ShapeType type)
{
    for (int i = 0; i < storage.getSize(); ++i) {
        Shape* sh = storage.at(i);
        bool matches = false;
        
        switch(type) {
        case ShapeType::Rect:
            matches = dynamic_cast<Rect*>(sh) != nullptr;
            break;
        case ShapeType::Ellipse:
            matches = dynamic_cast<Ell*>(sh) != nullptr;
            break;
        case ShapeType::Square:
            matches = dynamic_cast<Sqr*>(sh) != nullptr;
            break;
        case ShapeType::Circle:
            matches = dynamic_cast<Circ*>(sh) != nullptr;
            break;
        case ShapeType::Line:
            matches = dynamic_cast<Line*>(sh) != nullptr;
            break;
        case ShapeType::Triangle:
            matches = dynamic_cast<Triang*>(sh) != nullptr;
            break;
        }
        
        if (!ctrl) sh->setSelected(matches);
        else if (matches) sh->setSelected(!sh->isSelected());
    }
    update();
}