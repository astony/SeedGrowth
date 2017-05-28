#include "base.hpp"

Generator::Base::Base(int WidthMax, int HeightMax) : WidthMax(WidthMax), HeightMax(HeightMax)
{

}

void Generator::Base::SetWidthMax(int WidthMax)
{
    this->WidthMax = WidthMax;
}

void Generator::Base::SetHeightMax(int HeightMax)
{
    this->HeightMax = HeightMax;
}

QPoint Generator::Base::GetRandomPoint()
{
    std::uniform_int_distribution<int> DistributionX(0, WidthMax);
    std::uniform_int_distribution<int> DistributionY(0, HeightMax);
    return QPoint(DistributionX(RandomEngine), DistributionY(RandomEngine));
}

QColor Generator::Base::GetRandomColor()
{
    // to do
    // not always random probably
    return QColor(qrand() % 205 + 50, qrand() % 205 + 50, qrand() % 205 + 50);
}
