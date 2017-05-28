#ifndef GENERATOR_REGULAR_HPP
#define GENERATOR_REGULAR_HPP

#include "base.hpp"

namespace Generator
{
    class Regular : public Base
    {
    public:
        Regular(int WidthMax, int HeightMax);

        QVector<QPair<QPoint, QColor>>* generate();
    };
}

#endif // GENERATOR_REGULAR_HPP
