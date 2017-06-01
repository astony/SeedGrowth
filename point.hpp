#ifndef POINT_HPP
#define POINT_HPP

#include <QPoint>
#include <QColor>


class Point
{
public:
    Point();

    int getX();
    int getY();
    QColor getColor();
    bool getRecrystalized();
    bool getRecrystalizedPrev();

    void setX(int);
    void setY(int);
    void setColor(QColor);
    void setRecrystalized(bool);
    void setRecrystalizedPrev(bool);

private:
    QPoint point;
    QColor color;
    bool recrystalized;
    bool recrystalizedPrev;
    double ro;
};

#endif // POINT_HPP
