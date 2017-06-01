#ifndef GENERATOR_RANDOM_HPP
#define GENERATOR_RANDOM_HPP

#include "base.hpp"

namespace Generator
{
    class Random : public Base
    {
        Q_OBJECT

    public:
        Random(int WidthMax, int HeightMax);

        QVector<QPair<QPoint, QColor>>* generate();
        void FillPoints();
        void FillColors();

    protected:
        int UniqColorsCount;
        int UniqPointsCount;
    };
}

#endif // GENERATOR_RANDOM_HPP
