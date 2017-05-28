#include "random_with_radius.hpp"

Generator::RandomWithRadius::RandomWithRadius(int WidthMax, int HeightMax) : Base(WidthMax, HeightMax)
{

}

QVector<QPair<QPoint, QColor>>* Generator::RandomWithRadius::generate()
{
    bool RadiusDone = false;
    int RadiusInput = 15;

    RadiusInput = QInputDialog::getInt(0,
                                       "Generowanie",
                                       "Podaj promień",
                                       RadiusInput,
                                       2,
                                       WidthMax < HeightMax ? WidthMax / 2 : HeightMax / 2,
                                       1,
                                       &RadiusDone,
                                       Qt::WindowCloseButtonHint);

    if(RadiusDone == false)
        return nullptr;

    bool PointsDone = false;
    int PointsInput = 15;

    PointsInput = QInputDialog::getInt(0,
                                       "Generowanie",
                                       "Podaj liczbe punktów",
                                       PointsInput,
                                       2,
                                       RadiusInput * RadiusInput,
                                       1,
                                       &PointsDone,
                                       Qt::WindowCloseButtonHint);

    if(PointsDone == false)
        return nullptr;

    QVector<QPair<QPoint, QColor>> *GeneratedPoints = new QVector<QPair<QPoint, QColor>>;

    std::default_random_engine Generator;

    QPoint Point;
    QColor Color;

    Point = GetRandomPoint();
    Color = GetRandomColor();

    GeneratedPoints->push_back(QPair<QPoint, QColor>(Point, Color));

    emit PointGenerated(QPair<QPoint, QColor>(Point, Color));

    int RadiusXMin = Point.x() - RadiusInput;
    int RadiusXMax = Point.x() + RadiusInput;

    if(RadiusXMin < 0)
        RadiusXMin = 0;

    if(RadiusXMax > WidthMax)
        RadiusXMax = WidthMax;

    std::uniform_int_distribution<int> RadiusXDistribution(RadiusXMin, RadiusXMax);

    int RadiusYMin = Point.y() - RadiusInput;
    int RadiusYMax = Point.y() + RadiusInput;

    if(RadiusYMin < 0)
        RadiusYMin = 0;

    if(RadiusYMax > HeightMax)
        RadiusYMax = HeightMax;


    std::uniform_int_distribution<int> RadiusYDistribution(RadiusYMin, RadiusYMax);

    for(int i = 1; i < PointsInput; ++i)
    {
        Point = QPoint(RadiusXDistribution(Generator), RadiusYDistribution(Generator));
        Color = GetRandomColor();

        GeneratedPoints->push_back(QPair<QPoint, QColor>(Point, Color));

        emit PointGenerated(QPair<QPoint, QColor>(Point, Color));
    }

    return GeneratedPoints;
}
