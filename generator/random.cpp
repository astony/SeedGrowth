#include "random.hpp"

Generator::Random::Random(int WidthMax, int HeightMax) : Base(WidthMax, HeightMax)
{
    UniqPointsCount = 3600;
    UniqColorsCount = 100;

    FillPoints();
    FillColors();
}

void Generator::Random::FillPoints()
{
    QPoint RandomPoint;
    std::uniform_int_distribution<int> DistributionX(0, WidthMax);
    std::uniform_int_distribution<int> DistributionY(0, HeightMax);
    for(int i = 0; i < UniqPointsCount; ++i)
    {
        do
        {
            RandomPoint = QPoint(DistributionX(RandomEngine), DistributionY(RandomEngine));
        } while(Points.contains(RandomPoint));
        Points.push_back(RandomPoint);
    }
}

void Generator::Random::FillColors()
{
    QColor RandomColor;
    std::uniform_int_distribution<int> Distribution(0, 200);
    for(int i = 0; i < UniqColorsCount; ++i)
    {
        do
        {
            RandomColor = QColor(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RandomEngine));
        } while(Colors.contains(RandomColor));
        Colors.push_back(RandomColor);
    }
}

QVector<QPair<QPoint, QColor>>* Generator::Random::generate()
{
    bool PointsDone = false;
    int PointsInput = 15;

    PointsInput = QInputDialog::getInt(0,
                                 "Generowanie",
                                 "Podaj liczbe punktów",
                                 PointsInput,
                                 2,
                                 (WidthMax + 1) * (HeightMax + 1),
                                 1,
                                 &PointsDone,
                                 Qt::WindowCloseButtonHint);

    if(PointsDone == false)
        return nullptr;

    QVector<QPair<QPoint, QColor>> *GeneratedPoints = new QVector<QPair<QPoint, QColor>>;

    QPoint Point;
    QColor Color;

    int PointIndex, ColorIndex;

    for(int i = 0; i < PointsInput; ++i)
    {
        PointIndex = i;
        Point = Points.at(PointIndex);
        ColorIndex = i % (UniqColorsCount - 1);
        Color = Colors.at(ColorIndex);

        GeneratedPoints->push_back(QPair<QPoint, QColor>(Point, Color));

        emit PointGenerated(QPair<QPoint, QColor>(Point, Color));
    }

    return GeneratedPoints;
}
