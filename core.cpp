#include "core.h"
#include "ui_core.h"

Core::Core(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Core)
{
    ui->setupUi(this);
    this->setWindowTitle("MachBox");
}

Core::~Core()
{
    delete ui;
}
