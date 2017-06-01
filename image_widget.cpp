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
            QPoint(0, -1), QPoint(1, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(-1, 1), QPoint(0, 1)
        },
        {
            QPoint(-1, -1), QPoint(0, -1),
            QPoint(-1, 0), QPoint(1, 0),
            QPoint(0, 1), QPoint(1, 1)

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

        //QTest::qWait(0.01);

    } while(Points->size() < rowCount() * columnCount());

    emit GrowFinished();
}

void ImageWidget::Recrystalization()
{
    int Z = 0, RecNumber = 0;
    double Ro, RoAll = 0.0, PrevRo = 0.0;

    double A = 86710969050178.5;
    double B = 9.41268203527779;
    double t = 0.001;
    double dt = 0.001;

    bool Rec = true;

    QVector<double> PointsRo(Points->size(), 0.0);
    QVector<bool> PointsRecrystalized(Points->size(), false);
    QVector<bool> PointsRecrystalizedPrev(Points->size(), false);

    double CRITICAL_RO = ((A / B) + (1.0 - A / B) * qExp(-B * 0.065)) / (rowCount() * columnCount());

    while(Rec)
    {
        Ro = (A / B) + (1 - A / B) * qExp(-B * t) - PrevRo;

        for(int i = 0; i < Points->size(); ++i)
        {
            if(PointsRecrystalized.at(i) == false)
            {
                if(IsOnEdge(Points->at(i)))
                {
                    double a = 0.8 * (Ro / (rowCount() * columnCount()));
                    PointsRo[i] += a;
                    RoAll += a;

                }
                else
                {
                    double a = 0.2 * (Ro / (rowCount() * columnCount()));
                    PointsRo[i] += a;
                    RoAll += a;
                }
            }
            else
            {
                ++RecNumber;
            }
        }

        QVector<QPair<QPoint, QColor>> TmpPoints;

        std::default_random_engine RandomEngine;

        for(int i = 0; i < PointsRo.size(); ++i)
        {
            if(PointsRo.at(i) > CRITICAL_RO)
            {
                std::uniform_int_distribution<int> Distribution(0, 205);

                QColor NewColor = QColor(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RandomEngine));

                TmpPoints.push_back(QPair<QPoint, QColor>(Points->at(i).first, NewColor));

                PointsRo[i] = 0.0;
            }
        }

        QPoint TmpPoint;
        int TmpPointIndex;

        for(int i = 0; i < Points->size(); ++i)
        {
            if(PointsRecrystalized.at(i) == true)
            {
                QVector<QPoint> Length = { QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
                                            QPoint(-1, 0), QPoint(1, 0),
                                            QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1) };
                for(auto j : Length)
                {
                    TmpPoint = Points->at(i).first + j;
                    TmpPointIndex = FindPointIndex(TmpPoint);
                    if(IsValid(TmpPoint) && PointsRecrystalizedPrev.at(TmpPointIndex) == false)
                    {
                        TmpPoints.push_back(QPair<QPoint, QColor>(TmpPoint, Points->at(i).second));
                        PointsRo[TmpPointIndex] = 0.0;
                    }
                }
            }
        }

        double RoDiff = (Ro - RoAll) / (double)(10);

        int K = 0;

        std::uniform_int_distribution<int> PointsIndexDistribution(0, Points->size() - 1);

        for(int i = 0; i < Points->size(); ++i)
        {
            int index = PointsIndexDistribution(RandomEngine);

            if(K > 10)
            {
                break;
            }

            if(PointsRecrystalized.at(index) == false && IsOnEdge(Points->at(index)))
            {
                PointsRo[index] += RoDiff;
                K++;
            }
        }

        emit PopulatePixel(TmpPoints);
        ReplacePoint(TmpPoints);

        for(int i = 0; i < TmpPoints.size(); ++i)
        {
            int index = FindPointIndex(TmpPoints.at(i).first);
            PointsRo[index] = 0.0;
            PointsRecrystalized[index] = true;
            PointsRecrystalizedPrev[index] = PointsRecrystalized[index];
        }

        TmpPoints.clear();

        if(RecNumber == rowCount() * columnCount()){
            break;
        }

        PrevRo = Ro;
        t += dt;
        Z++;

        RecNumber = 0;
        RoAll = 0.0;

        QTest::qWait(1);

    }

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

    for(int i = 0; i < 2000; ++i)
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

        QTest::qWait(0.0000001);


    }

    emit MonteCarloFinished();
}

int ImageWidget::CalculateE(const QPair<QPoint, QColor> &Point)
{
    QPair<QPoint, QColor> TmpPoint;
    int count = 0;

    QVector<QPoint> Length = { QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1),
                                QPoint(-1, 0), QPoint(1, 0),
                                QPoint(-1, 1), QPoint(0, 1), QPoint(1, 1) };
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

int ImageWidget::FindPointIndex(const QPoint &Point)
{
    for(int i = 0; i < Points->size(); ++i)
        if(Points->at(i).first == Point)
            return i;
    return -1;
}

void ImageWidget::ReplacePoint(const QVector<QPair<QPoint, QColor>> &Point)
{
    for(auto i : Point)
        ReplacePoint(i);
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

bool ImageWidget::IsOnEdge(const QPair<QPoint, QColor> &Point)
{
    return CalculateE(Point) > 0;
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


