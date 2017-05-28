#include "options_tab.hpp"

OptionsTab::OptionsTab(QWidget *parent) : QWidget(parent)
{
    optionsLayout = new QVBoxLayout;

    neighborhoodGroup = new QButtonGroup;
    boundaryConditionGroup = new QButtonGroup;
    drawGroup = new QButtonGroup;

    optionsLayout->addWidget(InitNeighborhoodBox());
    optionsLayout->addWidget(InitBoundaryConditionBox());
    optionsLayout->addWidget(InitDrawBox());

    setLayout(optionsLayout);

    connect(neighborhoodGroup, SIGNAL(buttonClicked(int)), parent, SLOT(NeighborhoodGroupChanged(int)));
    connect(boundaryConditionGroup, SIGNAL(buttonClicked(int)), parent, SLOT(BoundaryConditionGroupChanged(int)));
    connect(drawGroup, SIGNAL(buttonClicked(int)), parent, SLOT(DrawGroupChanged(int)));
}

QGroupBox* OptionsTab::InitNeighborhoodBox()
{
    QGroupBox *neighborhoodBox = new QGroupBox(tr("Sąsiedztwo"));

    QRadioButton *radio1 = new QRadioButton(tr("Moore"));
    QRadioButton *radio2 = new QRadioButton(tr("Von Neumann"));
    QRadioButton *radio3 = new QRadioButton(tr("Heksagonal left"));
    QRadioButton *radio4 = new QRadioButton(tr("Heksagonal right"));
    QRadioButton *radio5 = new QRadioButton(tr("Hexagonal random"));
    QRadioButton *radio6 = new QRadioButton(tr("Pentagonal random"));

    neighborhoodGroup->addButton(radio1, 0);
    neighborhoodGroup->addButton(radio2, 1);
    neighborhoodGroup->addButton(radio3, 2);
    neighborhoodGroup->addButton(radio4, 3);
    neighborhoodGroup->addButton(radio5, 4);
    neighborhoodGroup->addButton(radio6, 5);

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(radio4);
    vbox->addWidget(radio5);
    vbox->addWidget(radio6);
    vbox->addStretch(1);

    neighborhoodBox->setLayout(vbox);

    return neighborhoodBox;
}

QGroupBox* OptionsTab::InitBoundaryConditionBox()
{
    QGroupBox *boundaryConditionBox = new QGroupBox(tr("Warunki brzegowe"));

    QRadioButton *radio1 = new QRadioButton(tr("Nieperiodyczne"));
    QRadioButton *radio2 = new QRadioButton(tr("Periodyczne"));

    boundaryConditionGroup->addButton(radio1, 0);
    boundaryConditionGroup->addButton(radio2, 1);

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);

    boundaryConditionBox->setLayout(vbox);

    return boundaryConditionBox;
}

QGroupBox* OptionsTab::InitDrawBox()
{
    QGroupBox *drawBox = new QGroupBox("Losowanie");

    QRadioButton *radio1 = new QRadioButton(tr("Losowe"));
    QRadioButton *radio2 = new QRadioButton(tr("Losowe z promieniem R"));
    QRadioButton *radio3 = new QRadioButton(tr("Równomierne"));

    drawGroup->addButton(radio1, 0);
    drawGroup->addButton(radio2, 1);
    drawGroup->addButton(radio3, 2);

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);

    drawBox->setLayout(vbox);

    return drawBox;
}

int OptionsTab::GetNeighborhoodValue()
{
    return neighborhoodGroup->checkedId();
}

int OptionsTab::GetBoundaryConditionValue()
{
    return boundaryConditionGroup->checkedId();
}

int OptionsTab::GetDrawValue()
{
    return drawGroup->checkedId();
}
