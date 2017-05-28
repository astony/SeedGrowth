#ifndef GUI_HPP
#define GUI_HPP

#include <QMainWindow>
#include <QHBoxLayout>
#include <QFont>
#include <QTime>
#include <QInputDialog>

#include "image_widget.hpp"
#include "tab_widget.hpp"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = 0);
    ~GUI();

private:
    QHBoxLayout *WindowLayout;

    ImageWidget *imageWidget;
    TabWidget *tabWidget;
};

#endif // GUI_H
