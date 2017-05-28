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

    bool isSimulationOn;

signals:
    void ProvideFeeds(int feeds);
    void ProvideIterations(int iterations);
    void ProvideSimulationTrigger(int value);

    void ProvideGenerate();
    void ProvideClean();

    void ColumnsChanged(int value);
    void RowsChanged(int value);
    void NeighborhoodChanged(int value);
    void BoundaryConditionChanged(int value);
    void DrawChanged(int value);

    void SimulationOn();
    void SimulationOff();

public slots:
    void SetFeeds(int feeds);
    void SetIterations(int iterations);
    void SetSimulationTrigger(int value);

    void ColumnChangerChanged(int value);
    void RowChangerChanged(int value);
    void NeighborhoodGroupChanged(int value);
    void BoundaryConditionGroupChanged(int value);
    void DrawGroupChanged(int value);

    void Generate();
    void Clean();

    void SimulationTrigger();
};

#endif // TAB_WIDGET_HPP
