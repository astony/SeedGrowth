#include "random.hpp"

Generator::Random::Random(int WidthMax, int HeightMax) : Base(WidthMax, HeightMax)
{

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
                                 WidthMax * HeightMax,
                                 1,
                                 &PointsDone,
                                 Qt::WindowCloseButtonHint);

    if(PointsDone == false)
        return nullptr;

    QVector<QPair<QPoint, QColor>> *GeneratedPoints = new QVector<QPair<QPoint, QColor>>;

    QPoint Point;
    QColor Color;

    for(int i = 0; i < PointsInput; ++i)
    {
        Point = GetRandomPoint();
        Color = GetRandomColor();

        GeneratedPoints->push_back(QPair<QPoint, QColor>(Point, Color));

        emit PointGenerated(QPair<QPoint, QColor>(Point, Color));
    }

    return GeneratedPoints;
}
