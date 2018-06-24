#include "headers/core.h"

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

Core::Core(QWidget *parent): QMainWindow(parent)
{
    this->setWindowTitle("MachBox");
    QMenu *file = menuBar()->addMenu("&File");
    QAction *loadm = file->addAction("&Load Mach-O");
    QAction *loadk = file->addAction("&Load KernelCache");
    QAction *quit = file->addAction("&Quit");
    QMenu *lle = menuBar()->addMenu("&LLE");
    QAction *loadv = lle->addAction("&Load SecureROM Dump");
    QAction *loadn = lle->addAction("&Load NOR Dump");
    QAction *loadb = lle->addAction("&Load Bootchain Components");
    QMenu *devices = menuBar()->addMenu("&Devices");
    QMenu* S5l8900X = devices->addMenu("&S5l8900");
    QAction* iPhone2G = S5l8900X->addAction("&iPhone 2G");
    QMenu *about = menuBar()->addMenu("&About");
    QAction *aboutm = about->addAction("&About MachBox");
    connect(loadm, &QAction::triggered, this, &Core::loadMacho);
    connect(loadk, &QAction::triggered, this, &Core::loadKernelCache);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(loadv, &QAction::triggered, this, &Core::loadVROM);
    connect(loadn, &QAction::triggered, this, &Core::loadNOR);
    connect(loadb, &QAction::triggered, this, &Core::loadBootChain);
    //connect(iPhone2G, &QAction::triggered, this, &PurpleSapphire::iPhone2GSetCPU);
    connect(aboutm, &QAction::triggered, this, &Core::aboutMachBox);
}

void Core::loadMacho()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Mach-O file"), "",
        tr("All Files (*)"));
}

void Core::loadKernelCache()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select KernelCache"), "",
        tr("All Files (*)"));
}

void Core::loadVROM()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select VROM [SecureROM]"), "",
        tr("All Files (*)"));
}

void Core::loadNOR()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select NOR Dump"), "",
        tr("All Files (*)"));
}

void Core::loadBootChain()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select iBoot/LLB"), "",
        tr("All Files (*)"));
}

void Core::aboutMachBox()
{
    QMessageBox::about(this,tr("MachBox"), tr("MachBox is a WIP LLE/HLE iOS Emulator.\n\nCopyright 2018"));
}

Core::~Core()
{

}
