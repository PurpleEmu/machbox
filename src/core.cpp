#include "core.h"

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

#include "ps/common.h"
#include "ps/arm.h"
#include "ps/iphone2g.h"
#include "ps/iphone3gs.h"

bool bootromhle;

Core::Core(QWidget *parent): QMainWindow(parent)
{
    this->setWindowTitle("MachBox");
    QMenu *file = menuBar()->addMenu("&File");
    QAction *loadm = file->addAction("&Load Mach-O");
    QAction *loadk = file->addAction("&Load KernelCache");
    QAction *quit = file->addAction("&Quit");
    QMenu *devices = menuBar()->addMenu("&Devices");
    QMenu* S5l8900X = devices->addMenu("&S5l8900");
    QAction* iPhone2G = S5l8900X->addAction("&iPhone 2G");
    QMenu *about = menuBar()->addMenu("&About");
    QAction *aboutm = about->addAction("&About MachBox");
    connect(loadm, &QAction::triggered, this, &Core::loadMacho);
    connect(loadk, &QAction::triggered, this, &Core::loadKernelCache);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(iPhone2G, &QAction::triggered, this, &Core::seliP2G);
    connect(aboutm, &QAction::triggered, this, &Core::aboutMachBox);
    /* disable until we need to enable */
    loadm->setEnabled(false);
    loadk->setEnabled(false);
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

void Core::aboutMachBox()
{
    QMessageBox::about(this,tr("MachBox"), tr("MachBox is a WIP LLE/HLE iOS Emulator.\n\nCopyright 2018"));
}

void Core::seliP2G()
{
    bool cont = true;
    QMessageBox::StandardButton icanhazhle = QMessageBox::question(this, "Use HLE?", "Would you like to HLE the bootrom?", QMessageBox::Yes|QMessageBox::No);
    if(icanhazhle == QMessageBox::Yes)
    {
        printf("HLEing the bootrom\n");
        bootromhle = true;
    }
    else
    {
        printf("Not HLEing the bootrom\n");
        bootromhle = false;
    }
    /* insanity */
    QString vromName = QFileDialog::getOpenFileName(this, tr("Select VROM"), "", tr("All Files (*)")); if(vromName.isEmpty()){printf("User didn't select VROM\n"); cont = false;}
    QString norName = QFileDialog::getOpenFileName(this, tr("Select NOR"), "", tr("All Files (*)")); if(norName.isEmpty()){printf("User didn't select NOR Dump\n"); cont = false;}
    QString iBootName = QFileDialog::getOpenFileName(this, tr("Select iBoot"), "", tr("All Files (*)")); if(iBootName.isEmpty()){printf("User didn't select iBoot\n"); cont = false;}
    while(cont)
    {
        /* convert qstrings to char for file */
        QByteArray vromx = vromName.toLatin1();
        QByteArray norx = norName.toLatin1();
        QByteArray iBootx = iBootName.toLatin1();
        //printf("everyone is alive\n");
        const char *vrom = vromx.data();
        const char *nor = norx.data();
        const char *iboot = iBootx.data();
        //printf("we survived the crash\n");
        //printf("sane: %s\n", vrom);
        //printf("sane: %s\n", nor);
        //printf("sane: %s\n", iboot);
        iphone2g* dev = (iphone2g*)malloc(sizeof(iphone2g));
        arm_cpu cpu;
        cpu.type = arm_type::arm11;
        cpu.init();
        dev->cpu = &cpu;
        dev->init();
        cpu.device = dev;    
        cpu.rw_real = iphone2g_rw;
        cpu.ww_real = iphone2g_ww;
        FILE* fp = fopen(vrom, "rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", vrom);
            break;
        }
        if(fread(dev->bootrom, 1, 0x10000, fp) != 0x10000)
        {
            printf("unable to load vrom\n");
            fclose(fp);
            break;
        }
        fclose(fp);
        fp = fopen(nor, "rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", nor);
            break;
        }
        s64 norsize = ftell(fp);
        if(fread(dev->nor, 1, 0x100000, fp) != 0x100000)
        {
            printf("unable to load nor\n");
            fclose(fp);
            break;
        }
        fclose(fp);
        if(bootromhle)
        {
            fp = fopen(iboot, "rb");
            if(!fp)
            {
                printf("unable to open %s, are you sure it exists?\n", iboot);
                break;
            }
            fseek(fp, 0, SEEK_END);
            s64 ibootsize = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            if(ibootsize == 0){printf("invalid iboot size of 0 bytes\n"); fclose(fp); break;}
            if(fread(dev->iboot, 1, ibootsize, fp) != ibootsize)
            {
                printf("unable to load iboot\n");
                fclose(fp);
                break;
            }
            fclose(fp);
            dev->init_hle();
        }
        else
        {
            memcpy(dev->lowram, dev->bootrom, 0x10000);
        }
        if(!bootromhle)
        {
            for(int i = 0; i < 40000; i++)
            {
                cpu.run(1);
                dev->tick();
            }
        }
        else
        {
            for(int i = 0; i < 300000; i++)
            {
                cpu.run(1);
                dev->tick();
            }
        }
        dev->exit();
        free(dev);
        break;
    }
}

Core::~Core()
{

}
