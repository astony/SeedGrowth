#ifndef GENERATOR_BASE_HPP
#define GENERATOR_BASE_HPP

#include <QObject>
#include <QVector>
#include <QPair>
#include <QPoint>
#include <QColor>
#include <QInputDialog>

namespace Generator
{
    class Base : public QObject
    {
        Q_OBJECT

    public:
        Base(int WidthMax, int HeightMax);
        
        virtual QVector<QPair<QPoint, QColor>>* generate() = 0;

        void SetWidthMax(int WidthMax);
        void SetHeightMax(int HeightMax);

        QPoint GetRandomPoint();
        QColor GetRandomColor();

    protected:
        int WidthMax;
        int HeightMax;

        QVector<QPoint> Points;
        QVector<QColor> Colors;

        std::default_random_engine RandomEngine;

    signals:
        void PointGenerated(const QPair<QPoint, QColor> &Point);
    };
}

#endif // GENERATOR_BASE_HPP
