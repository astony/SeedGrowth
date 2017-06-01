#include "general_tab.hpp"

GeneralTab::GeneralTab(QWidget *parent) : QWidget(parent)
{
    GeneralLayout = new QFormLayout;
    ColumnChanger = new QSpinBox;
    RowChanger = new QSpinBox;
    Growth = new QPushButton("Rozrost");
    Recrystallization = new QPushButton("Rekrystalizacja");
    MonteCarlo = new QPushButton("Monte Carlo");
    Generator = new QPushButton("Generuj");
    Cleaner = new QPushButton("Wyczyść");
    Feed = new QLCDNumber;
    Iteration = new QLCDNumber;

    Growth->setEnabled(false);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(false);

    GeneralLayout->addRow("Kolumn:", ColumnChanger);
    GeneralLayout->addRow("Wierszy:", RowChanger);

    ColumnChanger->setMinimum(20);
    ColumnChanger->setMaximum(300);

    RowChanger->setMinimum(20);
    RowChanger->setMaximum(250);

    ColumnChanger->setValue(60);
    RowChanger->setValue(60);

    Spacers.append(new QSpacerItem(10,15));
    GeneralLayout->addItem(Spacers.last());
    Feed->setSegmentStyle(QLCDNumber::Flat);
    Iteration->setSegmentStyle(QLCDNumber::Flat);
    GeneralLayout->addRow("Żyje:", Feed);
    GeneralLayout->addRow("Kroków:", Iteration);

    Feed->setDigitCount(7);
    Iteration->setDigitCount(7);

    Spacers.append(new QSpacerItem(10, 50));
    GeneralLayout->addItem(Spacers.last());
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Generator);

    Spacers.append(new QSpacerItem(10, 20));
    GeneralLayout->addItem(Spacers.last());
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Growth);
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Recrystallization);
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, MonteCarlo);

    Spacers.append(new QSpacerItem(10, 50));
    GeneralLayout->addItem(Spacers.last());
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Cleaner);

    setLayout(GeneralLayout);

    connect(ColumnChanger, SIGNAL(valueChanged(int)), parent, SLOT(ColumnChangerChanged(int)));
    connect(RowChanger, SIGNAL(valueChanged(int)), parent, SLOT(RowChangerChanged(int)));

    connect(Generator, SIGNAL(clicked()), parent, SLOT(Generate()));
    connect(Cleaner, SIGNAL(clicked()), parent, SLOT(Clean()));

    connect(Growth, SIGNAL(clicked()), parent, SLOT(GrowthTrigger()));
    connect(Recrystallization, SIGNAL(clicked()), parent, SLOT(RecrystallizationTrigger()));
    connect(MonteCarlo, SIGNAL(clicked()), parent, SLOT(MonteCarloTrigger()));
}

void GeneralTab::SetFeeds(int feeds)
{
    Feed->display(feeds);
}

void GeneralTab::SetIterations(int iterations)
{
    Iteration->display(iterations);
}

void GeneralTab::SetGrowthTrigger(int value)
{
    Growth->setEnabled(value);
}

void GeneralTab::SetRecrystallizationTrigger(int value)
{
    Recrystallization->setEnabled(value);
}

void GeneralTab::SetMonteCarloTrigger(int value)
{
    MonteCarlo->setEnabled(value);
}

void GeneralTab::Clean()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(false);

    Generator->setEnabled(true);
    ColumnChanger->setEnabled(true);
    RowChanger->setEnabled(true);

    SetFeeds(0);
    SetIterations(0);
}

void GeneralTab::InputsOn()
{
    ColumnChanger->setEnabled(true);
    RowChanger->setEnabled(true);
    Cleaner->setEnabled(true);
}

void GeneralTab::InputsOff()
{
    ColumnChanger->setEnabled(false);
    RowChanger->setEnabled(false);
    Cleaner->setEnabled(false);
}

void GeneralTab::GrowthOn()
{
    Growth->setEnabled(true);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(false);

    Generator->setEnabled(true);

    InputsOff();
}

void GeneralTab::GrowthOff()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(true);
    MonteCarlo->setEnabled(true);

    Generator->setEnabled(true);

    InputsOn();
}

void GeneralTab::RecrystallizationOn()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(true);
    MonteCarlo->setEnabled(false);

    Generator->setEnabled(false);

    InputsOff();
}

void GeneralTab::RecrystallizationOff()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(false);

    Generator->setEnabled(true);

    InputsOn();
}

void GeneralTab::MonteCarloOn()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(true);

    Generator->setEnabled(false);

    InputsOff();
}

void GeneralTab::MonteCarloOff()
{
    Growth->setEnabled(false);
    Recrystallization->setEnabled(false);
    MonteCarlo->setEnabled(false);

    Generator->setEnabled(true);

    InputsOn();
}
