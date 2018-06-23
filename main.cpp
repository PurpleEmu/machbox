#include "core.h"
#include "info.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Core w;
    w.show();
    printf("Welcome to MachBox %s\n", version);
    printf("Built on %s at %s\n", __DATE__, __TIME__);
    return a.exec();
}
