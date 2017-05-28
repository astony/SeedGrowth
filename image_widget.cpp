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

    GeneratorAlgorithms.push_back(new Generator::Random(rowCount(), columnCount()));
    GeneratorAlgorithms.push_back(new Generator::RandomWithRadius(rowCount(), columnCount()));
    GeneratorAlgorithms.push_back(new Generator::Regular(rowCount(), columnCount()));

    NeighborhoodPoints = {
        { QPoint(-1, -1), QPoint(-1, 0), QPoint(-1, 1),
          QPoint(0, -1), QPoint(0, 0), QPoint(0, 1),
          QPoint(1, -1), QPoint(1, 0), QPoint(1, 1)
        },
        { QPoint(-1, 0),
          QPoint(1, 0), QPoint(0, -1),
          QPoint(0, 1)
        },
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
    Points = GeneratorAlgorithms[GeneratorAlgorithmsValue]->generate();
}

void ImageWidget::Grow()
{
    int ActualPosition = 0;
    int i = 1;
    QVector<QPair<QPoint, QColor>> NewPoints;
    do
    {
        NewPoints = Points->mid(ActualPosition);
        ActualPosition = GrowStep(NewPoints);

        emit PointsChanged(NewPoints);
        emit IterationsChanged(i);

        ++i;
        QTest::qWait(100);

    } while(Points->size() < rowCount() * columnCount());

    emit GrowFinished();
}

int ImageWidget::GrowStep(QVector<QPair<QPoint, QColor>> NewPoints)
{
    QPoint NewPoint;
    QPoint ActualPoint;
    QColor ActualColor;

    int ActualPosition = Points->size() - 1;

    for(QPair<QPoint, QColor> Point : NewPoints)
    {
        ActualPoint = Point.first;
        ActualColor = Point.second;

        for(auto j : NeighborhoodPoints[NeighborhoodPointsValue])
        {
            NewPoint = ActualPoint + j;
            if(!IsPopulated(NewPoint) && IsPeriodic(NewPoint))
            {
                Points->push_back(QPair<QPoint, QColor>(NewPoint, ActualColor));
            }
        }
    }

    return ActualPosition;
}

bool ImageWidget::IsPopulated(const QPoint &Point)
{
    for(auto i : *Points)
        if(i.first == Point)
            return true;
    return false;
}

bool ImageWidget::IsPeriodic(const QPoint &Point)
{
    if(BoundaryConditionValue == 0)
        return Point.x() >= 0 &&
                Point.y() >= 0 &&
                Point.x() < rowCount() &&
                Point.y() < columnCount();
    return true;
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
    auto Item = item(Point.first.x(), Point.first.y());
    if(Item == nullptr)
    {
        Item = new QTableWidgetItem;
        setItem(Point.first.x(), Point.first.y(), Item);
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
    auto Item = item(Point.first.x(), Point.first.y());
    if(Item == nullptr)
    {
        Item = new QTableWidgetItem;
        setItem(Point.first.x(), Point.first.y(), Item);
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


