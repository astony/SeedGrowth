#ifndef OPTIONS_TAB_HPP
#define OPTIONS_TAB_HPP

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

class OptionsTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTab(QWidget *parent = 0);

    int GetNeighborhoodValue();
    int GetBoundaryConditionValue();
    int GetDrawValue();

private:
    QVBoxLayout *optionsLayout;

    QButtonGroup *neighborhoodGroup;
    QButtonGroup *boundaryConditionGroup;
    QButtonGroup *drawGroup;

    QGroupBox* InitNeighborhoodBox();
    QGroupBox* InitBoundaryConditionBox();
    QGroupBox* InitDrawBox();

signals:

public slots:
};

#endif // OPTIONS_TAB_HPP
