#include "nxndialog.h"
#include "ui_nxndialog.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>
#include <QTableView>

NxNDialog::NxNDialog( QWidget *parent, int x, int y, int opt, std::string firstName, std::string secondName ):
    QDialog(parent),
    ui(new Ui::NxNDialog),
    xParam(x),
    yParam(y),
    opt(opt),
    firstName(firstName),
    secondName(secondName)
{
    ui->setupUi(this);
    qDebug() << "x: " << xParam <<"y: " << yParam << "O: "<< opt;
    qDebug() << "fname: " << QString::fromStdString(firstName);
    qDebug() << "sname: " << QString::fromStdString(secondName);
    ui->teFile1->setText(firstName.c_str());
    ui->teFile2->setText(secondName.c_str());



}

NxNDialog::~NxNDialog()
{
    delete ui;
}




