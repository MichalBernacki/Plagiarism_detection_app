#include "nxnwindow.h"
#include "ui_nxnwindow.h"

NxNWindow::NxNWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NxNWindow)
{
    ui->setupUi(this);
}

NxNWindow::~NxNWindow()
{
    delete ui;
}
