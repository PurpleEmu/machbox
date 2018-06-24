#include "core.h"
#include "info.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Core mach;
    printf("Welcome to MachBox\n");
    printf("Version %s\nBuilt on %s at %s\n", version, __DATE__, __TIME__);
    mach.showMaximized();
    return app.exec();
}
