#ifndef NXNDIALOG_H
#define NXNDIALOG_H

#include <QDialog>
#include <string>
#include "project.h"
#include "result.h"

namespace Ui {
class NxNDialog;
}

class NxNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NxNDialog(QWidget *parent, int x, int y, int opt,  Result result);
    ~NxNDialog();

private slots:




private:
    Ui::NxNDialog *ui;

    int xParam;
    int yParam;
    int opt;
    Result result;

};

#endif // NXNDIALOG_H
