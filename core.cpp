#include "core.h"
#include "ui_core.h"

Core::Core(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Core)
{
    ui->setupUi(this);
}

Core::~Core()
{
    delete ui;
}
