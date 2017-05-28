#include "general_tab.hpp"

GeneralTab::GeneralTab(QWidget *parent) : QWidget(parent)
{
    GeneralLayout = new QFormLayout;
    ColumnChanger = new QSpinBox;
    RowChanger = new QSpinBox;
    Starter = new QPushButton("Start / Stop");
    Generator = new QPushButton("Generuj");
    Cleaner = new QPushButton("Wyczyść");
    Feed = new QLCDNumber;
    Iteration = new QLCDNumber;

    Starter->setEnabled(false);

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
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Starter);

    Spacers.append(new QSpacerItem(10, 50));
    GeneralLayout->addItem(Spacers.last());
    GeneralLayout->setWidget(GeneralLayout->rowCount(), QFormLayout::SpanningRole, Cleaner);

    setLayout(GeneralLayout);

    connect(ColumnChanger, SIGNAL(valueChanged(int)), parent, SLOT(ColumnChangerChanged(int)));
    connect(RowChanger, SIGNAL(valueChanged(int)), parent, SLOT(RowChangerChanged(int)));

    connect(Generator, SIGNAL(clicked()), parent, SLOT(Generate()));
    connect(Cleaner, SIGNAL(clicked()), parent, SLOT(Clean()));

    connect(Starter, SIGNAL(clicked()), parent, SLOT(SimulationTrigger()));
}

void GeneralTab::SetFeeds(int feeds)
{
    Feed->display(feeds);
}

void GeneralTab::SetIterations(int iterations)
{
    Iteration->display(iterations);
}

void GeneralTab::SetSimulationTrigger(int value)
{
    Starter->setEnabled(value);
}

void GeneralTab::Clean()
{
    Starter->setEnabled(true);
    Generator->setEnabled(true);
    ColumnChanger->setEnabled(true);
    RowChanger->setEnabled(true);

    SetFeeds(0);
    SetIterations(0);
}

void GeneralTab::SimulationOn()
{
    Cleaner->setEnabled(false);
    Starter->setEnabled(false);
    Generator->setEnabled(false);
    ColumnChanger->setEnabled(false);
    RowChanger->setEnabled(false);
}

void GeneralTab::SimulationOff()
{
    Cleaner->setEnabled(true);
    Starter->setEnabled(false);
    Generator->setEnabled(false);
    ColumnChanger->setEnabled(true);
    RowChanger->setEnabled(true);
}
