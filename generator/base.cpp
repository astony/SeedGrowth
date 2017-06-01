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
    if(Points.size() > 0)
    {
        std::uniform_int_distribution<int> Distribution(0, Points.size() - 1);
        return Points.at(Distribution(RandomEngine));
    }
    else
    {
        std::uniform_int_distribution<int> DistributionX(0, WidthMax);
        std::uniform_int_distribution<int> DistributionY(0, HeightMax);
        return QPoint(DistributionX(RandomEngine), DistributionY(RandomEngine));
    }
}

QColor Generator::Base::GetRandomColor()
{
    if(Colors.size() > 0)
    {
        std::uniform_int_distribution<int> Distribution(0, Colors.size() - 1);
        return Colors.at(Distribution(RandomEngine));
    }
    else
    {
        std::uniform_int_distribution<int> Distribution(0, 200);
        return QColor(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RandomEngine));
    }
}
