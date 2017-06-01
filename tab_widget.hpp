#ifndef TAB_WIDGET_HPP
#define TAB_WIDGET_HPP

#include <QTabWidget>

#include "general_tab.hpp"
#include "options_tab.hpp"

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget();

private:
    GeneralTab *generalTab;
    OptionsTab *optionsTab;

    bool IsGrowthOn;
    bool IsRecrystallizationOn;
    bool IsMonteCarloOn;

signals:
    void ProvideFeeds(int feeds);
    void ProvideIterations(int iterations);
    void ProvideGrowthTrigger(int value);

    void ProvideGenerate();
    void ProvideClean();

    void ColumnsChanged(int value);
    void RowsChanged(int value);
    void NeighborhoodChanged(int value);
    void BoundaryConditionChanged(int value);
    void DrawChanged(int value);

    void GrowthOn();
    void GrowthOff();

    void RecrystallizationOn();
    void RecrystallizationOff();

    void MonteCarloOn();
    void MonteCarloOff();

public slots:
    void SetFeeds(int feeds);
    void SetIterations(int iterations);
    void SetGrowthTrigger(int value);

    void ColumnChangerChanged(int value);
    void RowChangerChanged(int value);
    void NeighborhoodGroupChanged(int value);
    void BoundaryConditionGroupChanged(int value);
    void DrawGroupChanged(int value);

    void Generate();
    void Clean();

    void GrowthTrigger();
    void RecrystallizationTrigger();
    void MonteCarloTrigger();
};

#endif // TAB_WIDGET_HPP
