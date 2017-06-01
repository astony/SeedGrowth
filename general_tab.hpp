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

    void GrowthOn();
    void GrowthOff();

    void RecrystallizationOn();
    void RecrystallizationOff();

    void MonteCarloOn();
    void MonteCarloOff();

private:
    QFormLayout *GeneralLayout;
    QSpinBox *ColumnChanger;
    QSpinBox *RowChanger;
    QPushButton *Growth;
    QPushButton *Recrystallization;
    QPushButton *MonteCarlo;
    QPushButton *Generator;
    QPushButton *Cleaner;
    QVector <QSpacerItem *> Spacers;
    QLCDNumber *Feed;
    QLCDNumber *Iteration;

    void InputsOn();
    void InputsOff();

public slots:
    void SetFeeds(int feeds);
    void SetIterations(int iterations);
    void SetGrowthTrigger(int value);
    void SetRecrystallizationTrigger(int value);
    void SetMonteCarloTrigger(int value);
};

#endif // GENERAL_TAB_HPP
