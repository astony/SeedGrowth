#ifndef GENERAL_TAB_HPP
#define GENERAL_TAB_HPP

#include <QWidget>
#include <QTableWidget>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QVector>
#include <QLCDNumber>

class GeneralTab : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralTab(QWidget *parent = 0);

    void Clean();
    void SimulationOn();
    void SimulationOff();

private:
    QFormLayout *GeneralLayout;
    QSpinBox *ColumnChanger;
    QSpinBox *RowChanger;
    QPushButton *Starter;
    QPushButton *Generator;
    QPushButton *Cleaner;
    QVector <QSpacerItem *> Spacers;
    QLCDNumber *Feed;
    QLCDNumber *Iteration;

public slots:
    void SetFeeds(int feeds);
    void SetIterations(int iterations);
    void SetSimulationTrigger(int value);
};

#endif // GENERAL_TAB_HPP
