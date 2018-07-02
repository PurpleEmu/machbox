#ifndef CORE_H
#define CORE_H

#include <QMainWindow>

class Core : public QMainWindow
{
    Q_OBJECT
    public:
        Core(QWidget *parent = 0);
        void loadMacho();
        void loadKernelCache();
        void seliP2G();
        void aboutMachBox();
        ~Core();
};

#endif // CORE_H
