#include "gui.hpp"

GUI::GUI(QWidget *parent) : QMainWindow(parent)
{
    QFont f("Helvetica", 10);
    setFont(f);

    WindowLayout = new QHBoxLayout;
    imageWidget = new ImageWidget;
    tabWidget = new TabWidget;

    QWidget *mycentralwidget = new QWidget;
    mycentralwidget->setLayout(WindowLayout);

    setCentralWidget(mycentralwidget);
    setWindowTitle("Rozrost ziaren");
    setMinimumSize(680, 480);

    WindowLayout->addWidget(imageWidget);
    WindowLayout->addWidget(tabWidget);

    connect(imageWidget, SIGNAL(FeedsChanged(int)), tabWidget, SLOT(SetFeeds(int)));
    connect(imageWidget, SIGNAL(IterationsChanged(int)), tabWidget, SLOT(SetIterations(int)));
    connect(imageWidget, SIGNAL(GrowFinished()), tabWidget, SLOT(GrowthTrigger()));
    connect(imageWidget, SIGNAL(RecrystallizationFinished()), tabWidget, SLOT(RecrystallizationTrigger()));
    connect(imageWidget, SIGNAL(MonteCarloFinished()), tabWidget, SLOT(MonteCarloTrigger()));

    connect(tabWidget, SIGNAL(ColumnsChanged(int)), imageWidget, SLOT(ResizeColumns(int)));
    connect(tabWidget, SIGNAL(RowsChanged(int)), imageWidget, SLOT(ResizeRows(int)));

    connect(tabWidget, SIGNAL(NeighborhoodChanged(int)), imageWidget, SLOT(SetNeighborhoodPointsValue(int)));
    connect(tabWidget, SIGNAL(BoundaryConditionChanged(int)), imageWidget, SLOT(SetBoundaryConditionValue(int)));
    connect(tabWidget, SIGNAL(DrawChanged(int)), imageWidget, SLOT(SetGeneratorAlgorithmsValue(int)));

    connect(tabWidget, SIGNAL(ProvideGenerate()), imageWidget, SLOT(Generate()));
    connect(tabWidget, SIGNAL(ProvideClean()), imageWidget, SLOT(Clean()));

    connect(tabWidget, SIGNAL(GrowthOn()), imageWidget, SLOT(Grow()));
    connect(tabWidget, SIGNAL(RecrystallizationOn()), imageWidget, SLOT(Recrystalization()));
    connect(tabWidget, SIGNAL(MonteCarloOn()), imageWidget, SLOT(MonteCarlo()));

    qsrand(QTime::currentTime().msecsTo(QTime(0, 0, 0, 0)));
}

GUI::~GUI()
{

}
