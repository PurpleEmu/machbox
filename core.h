#ifndef CORE_H
#define CORE_H

#include <QMainWindow>

namespace Ui {
class Core;
}

class Core : public QMainWindow
{
    Q_OBJECT

public:
    explicit Core(QWidget *parent = 0);
    ~Core();

private:
    Ui::Core *ui;
};

#endif // CORE_H
