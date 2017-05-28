#ifndef GENERATOR_RANDOM_WITH_RADIUS_HPP
#define GENERATOR_RANDOM_WITH_RADIUS_HPP

#include "base.hpp"
#include <random>

namespace Generator
{
    class RandomWithRadius : public Base
    {
    public:
        RandomWithRadius(int WidthMax, int HeightMax);

        QVector<QPair<QPoint, QColor>>* generate();
    };
}

#endif // GENERATOR_RANDOM_WITH_RADIUS_HPP
