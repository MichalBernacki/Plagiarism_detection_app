#include "nxndialog.h"
#include "ui_nxndialog.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>
#include <QTableView>

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


