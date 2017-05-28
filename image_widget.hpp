#ifndef IMAGE_WIDGET_HPP
#define IMAGE_WIDGET_HPP

#include <QTableWidget>
#include <QHeaderView>
#include <QGridLayout>
#include <QTest>

#include "generator/base.hpp"
#include "generator/random.hpp"
#include "generator/random_with_radius.hpp"
#include "generator/regular.hpp"

class ImageWidget : public QTableWidget
{
    Q_OBJECT
    Q_ENUMS(GeneratorAlgorithmsEnum NeighborhoodPointsEnum)

public:
    explicit ImageWidget(QWidget *Parent = 0);

    enum GeneratorAlgorithmsEnum {
        RANDOM = 0,
        RANDOM_WITH_RADIUS = 1,
        REGULAR = 2
    };
    enum NeighborhoodPointsEnum {
        VON_NEUMANN = 0,
        MOORE = 1,
        HEXAGONAL_LEFT = 2,
        HEXAGONAL_RIGHT = 3,
        HEXAGONAL_RANDOM = 4,
        PENTAGONAL_RANDOM = 5
    };

    QColor GetRandomColor();
    QColor GetKillColor();

private:
    int FeedsCount;
    int IterationCount;

    QVector<QPair<QPoint, QColor>> *Points;

    QVector<QVector<QPoint>> NeighborhoodPoints;
    int NeighborhoodPointsValue;

    QVector<Generator::Base*> GeneratorAlgorithms;
    int GeneratorAlgorithmsValue;

    int BoundaryConditionValue;

    bool IsPopulated(const QPoint &Point);
    bool IsPeriodic(const QPoint &Point);
    int GrowStep(QVector<QPair<QPoint, QColor>> NewPoints);

signals:
    void FeedsChanged(int Feeds);
    void IterationsChanged(int Iterations);
    void SimulationTriggerButtonChanged(int Feeds);

    void PointsChanged(const QPair<QPoint, QColor> &Point);
    void PointsChanged(const QVector<QPair<QPoint, QColor>> &Points);

    void GrowFinished();

public slots:
    void Clean();
    void Generate();
    void Grow();
    void ResizeRows(const int &Rows);
    void ResizeColumns(const int &Columns);
    void PopulatePixel(const QVector<QPair<QPoint, QColor>> &Points);
    void PopulatePixel(const QPair<QPoint, QColor> &Point);
    void KillPixel(const QPair<QPoint, QColor> &Point);
    void SetNeighborhoodPointsValue(const int &value);
    void SetGeneratorAlgorithmsValue(const int &value);
    void SetBoundaryConditionValue(const int &value);
};

#endif // IMAGE_WIDGET_HPP
