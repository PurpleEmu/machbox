#ifndef CORE_H
#define CORE_H

#include <QMainWindow>

class Core : public QMainWindow
{
    Q_OBJECT
    public:
        Core(QWidget *parent = 0);
        ~Core();
        void loadMacho();
        void loadKernelCache();
        void seliP2G();
        void seliP3GS();
        void aboutMachBox();
};

#endif // CORE_H
