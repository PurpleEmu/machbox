#ifndef CORE_H
#define CORE_H

#include <QMainWindow>

class Core : public QMainWindow
{
    Q_OBJECT

public:
    Core(QWidget *parent = 0);
    ~Core();
};

#endif // CORE_H
