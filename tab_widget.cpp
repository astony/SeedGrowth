#include "tab_widget.hpp"

TabWidget::TabWidget()
{
    isSimulationOn = false;

    generalTab = new GeneralTab(this);
    optionsTab = new OptionsTab(this);
    addTab(generalTab, tr("Główne Opcje"));
    addTab(optionsTab, tr("Dodatkowe Opcje"));

    setMaximumWidth(240);

    connect(this, SIGNAL(ProvideFeeds(int)), generalTab, SLOT(SetFeeds(int)));
    connect(this, SIGNAL(ProvideIterations(int)), generalTab, SLOT(SetIterations(int)));
    connect(this, SIGNAL(ProvideSimulationTrigger(int)), generalTab, SLOT(SetSimulationTrigger(int)));
}

void TabWidget::SetFeeds(int feeds)
{
    emit ProvideFeeds(feeds);
}

void TabWidget::SetIterations(int iterations)
{
    emit ProvideIterations(iterations);
}

void TabWidget::SetSimulationTrigger(int value)
{
    emit ProvideSimulationTrigger(value);
}

void TabWidget::ColumnChangerChanged(int value)
{
    emit ColumnsChanged(value);
}

void TabWidget::RowChangerChanged(int value)
{
    emit RowsChanged(value);
}

void TabWidget::NeighborhoodGroupChanged(int value)
{
    emit NeighborhoodChanged(value);
}

void TabWidget::BoundaryConditionGroupChanged(int value)
{
    emit BoundaryConditionChanged(value);
}

void TabWidget::DrawGroupChanged(int value)
{
    emit DrawChanged(value);
}

void TabWidget::SimulationTrigger()
{
    isSimulationOn = !isSimulationOn;

    if(isSimulationOn)
    {
        generalTab->SimulationOn();
        emit SimulationOn();
    }
    else
    {
        generalTab->SimulationOff();
        emit SimulationOff();
    }
}

void TabWidget::Generate()
{
    generalTab->SetSimulationTrigger(true);
    emit ProvideGenerate();
}

void TabWidget::Clean()
{
    generalTab->Clean();
    emit ProvideClean();
}


