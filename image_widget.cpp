#include "image_widget.hpp"

ImageWidget::ImageWidget(QWidget *Parent) : QTableWidget(Parent)
{
    FeedsCount = 0;
    IterationCount = 0;

    NeighborhoodPointsValue = 0;
    GeneratorAlgorithmsValue = 0;

    setSelectionMode(QTableWidget::NoSelection);
    setShowGrid(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();

    ResizeRows(60);
    ResizeColumns(60);

    GeneratorAlgorithms.push_back(new Generator::Random(rowCount() - 1, columnCount() - 1));
    GeneratorAlgorithms.push_back(new Generator::RandomWithRadius(rowCount() - 1, columnCount() - 1));
    GeneratorAlgorithms.push_back(new Generator::Regular(rowCount() - 1, columnCount() - 1));

    NeighborhoodPoints = {
        {
            QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1)
        },
        {
            QPoint(0, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(0, 1)
        },
        {
            QPoint(-1, -1), QPoint(0, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(-1, 1), QPoint(1, 1)

        },
        {
            QPoint(0, -1), QPoint(1, -1),
            QPoint(-1, 0),
            QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1)
        },
        {
            QPoint(0, -1), QPoint(1, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(-1, -1), QPoint(1, 1)
        },
        {
            QPoint(0, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(-1, 1), QPoint(1, 1)
        }
    };

    for(auto algorithm : GeneratorAlgorithms)
        connect(algorithm, SIGNAL(PointGenerated(QPair<QPoint, QColor>)), this, SLOT(PopulatePixel(QPair<QPoint, QColor>)));

    connect(this, SIGNAL(PointsChanged(QPair<QPoint, QColor>)), this, SLOT(PopulatePixel(QPair<QPoint, QColor>)));
    connect(this, SIGNAL(PointsChanged(QVector<QPair<QPoint, QColor>>)), this, SLOT(PopulatePixel(QVector<QPair<QPoint, QColor>>)));
}

void ImageWidget::Clean()
{
    clearContents();
    Points->clear();

    FeedsCount = 0;
    IterationCount = 0;
}

void ImageWidget::Generate()
{
    if(Points == nullptr)
        Points = GeneratorAlgorithms[GeneratorAlgorithmsValue]->generate();
    else
        Points->append(*GeneratorAlgorithms[GeneratorAlgorithmsValue]->generate());
}

void ImageWidget::Grow()
{
    QPoint NewPoint;
    QPoint ActualPoint;
    QColor ActualColor;

    int i = 0;

    do
    {

        ActualPoint = Points->at(i).first;
        ActualColor = Points->at(i).second;

        for(auto j : NeighborhoodPoints[NeighborhoodPointsValue])
        {
            NewPoint = ActualPoint + j;

            if(NewPoint.x() < 0 )

            if(BoundaryConditionValue == 1)
            {
                if(NewPoint.x() < 0)
                    NewPoint.setX(rowCount() + NewPoint.x());
                if(NewPoint.y() < 0)
                    NewPoint.setY(columnCount() + NewPoint.y());
                if(NewPoint.x() >= rowCount())
                    NewPoint.setX(1 - rowCount() + NewPoint.x());
                if(NewPoint.y() >= columnCount())
                    NewPoint.setY(1 - columnCount() + NewPoint.y());
            }


            if(!IsPopulated(NewPoint) && IsValid(NewPoint))
            {
                Points->push_back(QPair<QPoint, QColor>(NewPoint, ActualColor));
                emit PointsChanged(QPair<QPoint, QColor>(NewPoint, ActualColor));
            }
        }

        ++i;

        QTest::qWait(0.1);

    } while(Points->size() < rowCount() * columnCount());

    emit GrowFinished();
}

void ImageWidget::Recrystalization()
{
//    int Z = 0, RecNumber = 0;
//    double Ro, RoAll = 0.0, PrevRo = 0.0;

//    double A = 86710969050178.5;
//    double B = 9.41268203527779;
//    double t = 0.001;
//    double dt = 0.001;
//    bool Rec = true;

//    QVector<double> PointsRo = QVector(Points->size(), 0);
//    QVector<bool> PointsRecrystalized = QVector(Points->size(), false);
//    QVector<bool> PointsRecrystalizedPrev = QVector(Points->size(), false);

//    double CRITICAL_RO = ((A / B) + (1 - A / B) * exp(-B * 0.065)) / rowCount() * columnCount();

//    while(Rec)
//    {
//        Ro = (A / B) + (1 - A / B) * exp(-B * t) - PrevRo;

//        for(int i = 0; i < Points->size(); ++i)
//        {
//            if(PointsRecrystalized.at(i) == false)
//            {
//                double a;
//                if(IsOnEdge(Points->at(i)))
//                {
//                    a = 0.8 * (Ro / rowCount() * columnCount());

//                }
//                else
//                {
//                    a = 0.2 * (Ro / rowCount() * columnCount());
//                }
//                PointsRo.at(i) += a;
//                RoAll += a;
//            }
//            else
//            {
//                ++RecNumber;
//            }
//        }

//        for(int i = 0; i < PointsRo.size(); ++i)
//        {
//            if(PointsRo.at(i) > CRITICAL_RO)
//            {
//                std::default_random_engine RandomEngine;

//                std::uniform_int_distribution<int> Distribution(0, 205);

//                QColor NewColor = QColor(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RndomEngine));

//                ReplacePoint(QPair<QPoint, QColor>(Points->at(i).first, NewColor));

//                emit PopulatePixel(Points->at(i));

//                PointsRo.at(i) = 0;
//            }
//        }

//        for(int i = 0; i < Points->size(); ++i)
//        {
//            if(PointsRecrystalized.at(i) == true)
//            {
//                // Neighbooorhood
//            }
//        }

//        double RoDiff = (Ro - RoAll) / (double)(10);

//        std::random_shuffle(Points->begin(), Points->end());

//        int K = 0;

//        for(int i = 0; i < Points->size(); ++i)
//        {
//            if(K > 10)
//            {
//                break;
//            }

//            if(PointsRecrystalized.at(i) == true && IsOnEdge(Points->at(i)))
//            {
//                PointsRo.at(i) += RoDiff;
//                K++;
//            }
//        }

//        PrevRo = Ro;
//        t += dt;
//        Z++;
//    }

    emit RecrystallizationFinished();
}

void ImageWidget::MonteCarlo()
{
    if(Points->size() != rowCount() * columnCount())
    {
        QMessageBox msgBox;
        msgBox.setText("Wygeneruj całą plansze");
        msgBox.exec();
        emit MonteCarloFinished();

        return;
    }

    for(int i = 0; i < 200; ++i)
    {

        QVector<QPoint> TmpPoints;
        QVector<QColor> TmpColors;

        for(auto Point : *Points)
        {
            TmpPoints.push_back(Point.first);
            if(!TmpColors.contains(Point.second))
                TmpColors.push_back(Point.second);
        }

        std::random_shuffle(TmpPoints.begin(), TmpPoints.end());

        std::default_random_engine RandomEngine;

        std::uniform_int_distribution<int> ColorDistribution(0, TmpColors.size() - 1);

        while(TmpPoints.size() > 0)
        {
            int RandomColorValue = ColorDistribution(RandomEngine);

            QPair<QPoint, QColor> Point = FindPoint(TmpPoints.first());
            QPair<QPoint, QColor> NewPoint(Point.first, TmpColors.at(RandomColorValue));

            int E1 = CalculateE(Point);
            int E2 = CalculateE(NewPoint);

            if(E2 <= E1)
            {
                ReplacePoint(NewPoint);
                emit PopulatePixel(NewPoint);
            }

            TmpPoints.pop_front();

        }

        QTest::qWait(10);


    }

    emit MonteCarloFinished();
}

int ImageWidget::CalculateE(const QPair<QPoint, QColor> &Point)
{
    QPair<QPoint, QColor> TmpPoint;
    int count = 0;

    QVector<QPoint> Length = { QPoint(-1, -1), QPoint(-1, 0), QPoint(-1, 1),
                                QPoint(0, -1), QPoint(0, 1),
                                QPoint(1, -1), QPoint(1, 0), QPoint(1, 1) };
    for(auto j : Length)
    {
        TmpPoint = FindPoint(Point.first + j);
        if(TmpPoint.second != Point.second)
            count++;
    }
    return count;
}

QPair<QPoint, QColor> ImageWidget::FindPoint(const QPoint &Point)
{
    for(auto i : *Points)
        if(i.first == Point)
            return i;
}

void ImageWidget::ReplacePoint(const QPair<QPoint, QColor> &Point)
{
    for(int i = 0; i < Points->size(); ++i)
        if(Points->at(i).first == Point.first)
            Points->replace(i, Point);
}

bool ImageWidget::IsPopulated(const QPoint &Point)
{
    for(auto i : *Points)
        if(i.first == Point)
            return true;
    return false;
}

bool ImageWidget::IsValid(const QPoint &Point)
{
    return Point.x() >= 0 && Point.y() >= 0 && Point.y() < rowCount() && Point.x() < columnCount();
}

void ImageWidget::ResizeRows(const int &Rows)
{
    if(rowCount() == Rows)
        return;

    int oldRows = this->rowCount();
    int lifeCropped = 0;

    QTableWidgetItem *Item;

    //Gdy wierszy jest mniej
    for(int i = Rows; i < oldRows; ++i)
    {
        for(int j = 0; j < columnCount(); ++j)
        {
            Item = item(i,j);
            if(Item == 0)
                continue;
            if(Item->data(Qt::UserRole) == true)
                ++lifeCropped;
        }
    }

    if(lifeCropped > 0)
        emit FeedsChanged(FeedsCount - lifeCropped);

    setRowCount(Rows);

    //Gdy wierszy jest więcej
    for(int i = oldRows; i < Rows; ++i)
    {
        setRowHeight(i, 5);
    }

    for(auto algorithm : GeneratorAlgorithms)
        algorithm->SetWidthMax(Rows);

    // emit NewRows(Rows);
}

void ImageWidget::ResizeColumns(const int &Columns)
{
    if(columnCount() == Columns)
        return;

    int oldColumns = columnCount();
    int lifeCropped = 0;

    QTableWidgetItem *Item;

    //Gdy kolumn jest mniej
    for(int i = Columns; i < oldColumns; ++i)
    {
        for(int j = 0; j < rowCount(); ++j)
        {
            Item = item(j, i);
            if(Item == 0)
                continue;
            if(Item->data(Qt::UserRole) == true)
                ++lifeCropped;
        }
    }

    if(lifeCropped > 0)
        emit FeedsChanged(FeedsCount - lifeCropped);

    setColumnCount(Columns);

    //Gdy kolumn jest więcej
    for(int i = oldColumns; i < Columns; ++i)
    {
        setColumnWidth(i, 5);
    }

    for(auto algorithm : GeneratorAlgorithms)
        algorithm->SetHeightMax(Columns);

    // emit NewCols(Columns);
}

void ImageWidget::PopulatePixel(const QVector<QPair<QPoint, QColor>> &Points)
{
    for(auto Point : Points)
        PopulatePixel(Point);
}

/*
 * Populate Pixel on position with random color
 */
void ImageWidget::PopulatePixel(const QPair<QPoint, QColor> &Point)
{
    auto Item = item(Point.first.y(), Point.first.x());
    if(Item == nullptr)
    {
        Item = new QTableWidgetItem;
        setItem(Point.first.y(), Point.first.x(), Item);
    }
    Item->setData(Qt::UserRole, QVariant(true));
    Item->setBackgroundColor(Point.second);
    ++FeedsCount;
    emit FeedsChanged(FeedsCount);
}

/*
 * Kill Pixel on position with kill color
 */
void ImageWidget::KillPixel(const QPair<QPoint, QColor> &Point)
{
    auto Item = item(Point.first.y(), Point.first.x());
    if(Item == nullptr)
    {
        Item = new QTableWidgetItem;
        setItem(Point.first.y(), Point.first.x(), Item);
    }
    Item->setData(Qt::UserRole, QVariant(false));
    Item->setBackgroundColor(QColor("white"));
    --FeedsCount;
    emit FeedsChanged(FeedsCount);
}

void ImageWidget::SetNeighborhoodPointsValue(const int &value)
{
    NeighborhoodPointsValue = value;
}

void ImageWidget::SetGeneratorAlgorithmsValue(const int &value)
{
    GeneratorAlgorithmsValue = value;
}

void ImageWidget::SetBoundaryConditionValue(const int &value)
{
    BoundaryConditionValue = value;
}


