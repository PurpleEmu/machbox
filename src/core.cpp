#include "core.h"

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>

Core::Core(QWidget *parent): QMainWindow(parent)
{
    this->setWindowTitle("MachBox");
    QMenu *file;
    file = menuBar()->addMenu("&File");
    QAction *loadm = new QAction("&Load Mach-O", this);
    QAction *loadk = new QAction("&Load KernelCache", this);
    QAction *quit = new QAction("&Quit", this);
    file->addAction(loadm);
    file->addAction(loadk);
    file->addAction(quit);
    QMenu *lle;
    lle = menuBar()->addMenu("&LLE");
    QAction *loadv = new QAction("&Load SecureROM Dump", this);
    QAction *loadn = new QAction("&Load NOR Dump", this);
    QAction *loadb = new QAction("&Load Bootchain Components", this);
    lle->addAction(loadv);
    lle->addAction(loadn);
    lle->addAction(loadb);
    QMenu *about;
    about = menuBar()->addMenu("&About");
    QAction *aboutm = new QAction("&About MachBox", this);
    about->addAction(aboutm);
    connect(loadm, &QAction::triggered, this, &Core::loadMacho);
    connect(loadk, &QAction::triggered, this, &Core::loadKernelCache);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(loadv, &QAction::triggered, this, &Core::loadVROM);
    connect(loadn, &QAction::triggered, this, &Core::loadNOR);
    connect(loadb, &QAction::triggered, this, &Core::loadBootChain);
    //connect(aboutm, &QAction::triggered, this, QApplication::quit);
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

Core::~Core()
{

}
