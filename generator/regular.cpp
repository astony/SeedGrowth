#include "regular.hpp"

Generator::Regular::Regular(int WidthMax, int HeightMax) : Base(WidthMax, HeightMax)
{

}

QVector<QPair<QPoint, QColor>>* Generator::Regular::generate()
{
    bool LengthDone = false;
    int LengthInput = 15;

    LengthInput = QInputDialog::getInt(0,
                                       "Generowanie",
                                       "Podaj odległość",
                                       LengthInput,
                                       2,
                                       WidthMax * HeightMax,
                                       1,
                                       &LengthDone,
                                       Qt::WindowCloseButtonHint);

    if(LengthDone == false)
        return nullptr;

    QVector<QPair<QPoint, QColor>> *GeneratedPoints = new QVector<QPair<QPoint, QColor>>;

    QPoint Point;
    QColor Color;

    for(int i = 1; i < WidthMax / LengthInput; ++i)
    {
        for(int j = 1; j < HeightMax / LengthInput; ++j)
        {
            Point = QPoint(LengthInput * i, LengthInput * j);
            Color = GetRandomColor();

            GeneratedPoints->push_back(QPair<QPoint, QColor>(Point, Color));

            emit PointGenerated(QPair<QPoint, QColor>(Point, Color));
        }
    }

    return GeneratedPoints;
}
