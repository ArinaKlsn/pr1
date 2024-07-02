#ifndef QSHAPE_H
#define QSHAPE_H

#include <QColor>
#include <QRect>
#include <QLine>
#include <QPolygon>
#include <QBrush>

class QShape
{
public:
    QShape() : isEllipse(false), isFilled(false), isPolygon(false) {}
    QShape(const QLine &line, const QColor &color, const QBrush &brush = QBrush())
        : line(line), color(color), brush(brush), isEllipse(false), isFilled(false), isPolygon(false) {}
    QShape(const QRect &rect, const QColor &color, bool isEllipse = false, bool isFilled = false, const QBrush &brush = QBrush())
        : rect(rect), color(color), brush(brush), isEllipse(isEllipse), isFilled(isFilled), isPolygon(false) {}
    QShape(const QPolygon &polygon, const QColor &color, bool isFilled = false, const QBrush &brush = QBrush())
        : polygon(polygon), color(color), brush(brush), isEllipse(false), isFilled(isFilled), isPolygon(true) {}

    QLine line;
    QRect rect;
    QPolygon polygon;
    QColor color;
    QBrush brush;
    bool isEllipse;
    bool isFilled;
    bool isPolygon;
};

#endif // QSHAPE_H
