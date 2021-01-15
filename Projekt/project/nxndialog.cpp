#include "nxndialog.h"
#include "ui_nxndialog.h"

NxNDialog::NxNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NxNDialog)
{
    ui->setupUi(this);
}

NxNDialog::~NxNDialog()
{
    delete ui;
}
