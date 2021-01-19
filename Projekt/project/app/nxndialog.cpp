#include "nxndialog.h"
#include "ui_nxndialog.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>
#include <QTableView>

NxNDialog::NxNDialog( QWidget *parent, int x, int y, int opt) :
    QDialog(parent),
    ui(new Ui::NxNDialog),
    xParam(x),
    yParam(y),
    opt(opt)
{
    ui->setupUi(this);
    qDebug() << "x: " << xParam <<"y: " << yParam << "O: "<< opt;

}

NxNDialog::~NxNDialog()
{
    delete ui;
}




