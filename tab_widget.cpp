#include "tab_widget.hpp"

TabWidget::TabWidget()
{
    IsGrowthOn = false;
    IsRecrystallizationOn = false;
    IsMonteCarloOn = false;

    generalTab = new GeneralTab(this);
    optionsTab = new OptionsTab(this);

    addTab(generalTab, tr("Główne Opcje"));
    addTab(optionsTab, tr("Dodatkowe Opcje"));

    setMaximumWidth(240);

    connect(this, SIGNAL(ProvideFeeds(int)), generalTab, SLOT(SetFeeds(int)));
    connect(this, SIGNAL(ProvideIterations(int)), generalTab, SLOT(SetIterations(int)));
    connect(this, SIGNAL(ProvideGrowthTrigger(int)), generalTab, SLOT(SetGrowthTrigger(int)));
}

void TabWidget::SetFeeds(int feeds)
{
    emit ProvideFeeds(feeds);
}

void TabWidget::SetIterations(int iterations)
{
    emit ProvideIterations(iterations);
}

void TabWidget::SetGrowthTrigger(int value)
{
    emit ProvideGrowthTrigger(value);
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

void TabWidget::GrowthTrigger()
{
    IsGrowthOn = !IsGrowthOn;

    if(IsGrowthOn)
    {
        generalTab->GrowthOn();
        emit GrowthOn();
    }
    else
    {
        generalTab->GrowthOff();
        emit GrowthOff();
    }
}

void TabWidget::RecrystallizationTrigger()
{
    IsRecrystallizationOn = !IsRecrystallizationOn;

    if(IsRecrystallizationOn)
    {
        generalTab->RecrystallizationOn();
        emit RecrystallizationOn();
    }
    else
    {
        generalTab->RecrystallizationOff();
        emit RecrystallizationOff();
    }
}

void TabWidget::MonteCarloTrigger()
{
    IsMonteCarloOn = !IsMonteCarloOn;

    if(IsMonteCarloOn)
    {
        generalTab->MonteCarloOn();
        emit MonteCarloOn();
    }
    else
    {
        generalTab->MonteCarloOff();
        emit MonteCarloOff();
    }
}

void TabWidget::Generate()
{
    generalTab->SetGrowthTrigger(true);
    generalTab->SetRecrystallizationTrigger(true);
    generalTab->SetMonteCarloTrigger(true);
    emit ProvideGenerate();
}

void TabWidget::Clean()
{
    generalTab->Clean();
    emit ProvideClean();
}


