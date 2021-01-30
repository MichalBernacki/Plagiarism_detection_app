#include "nxndialog.h"
#include "ui_nxndialog.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>
#include <QTableView>

NxNDialog::NxNDialog( QWidget *parent, int x, int y, int opt, Result result):
    QDialog(parent),
    ui(new Ui::NxNDialog),
    xParam(x),
    yParam(y),
    opt(opt),
    result(result)
{
    ui->setupUi(this);
    //qDebug() << "x: " << xParam <<"y: " << yParam << "O: "<< opt;
    qDebug() << QString::fromStdString(result.algorithmName);
   // ui->teFile1->setText( (result.bestMatch1->m_OriginalContent).c_str() );
   // ui->teFile2->setText(result.bestMatch2->m_OriginalContent.c_str());
   //qDebug() << QString::fromStdString(result.bestMatch1->m_OriginalContent);
}

NxNDialog::~NxNDialog()
{
    delete ui;
}




