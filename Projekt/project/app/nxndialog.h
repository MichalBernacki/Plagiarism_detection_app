#ifndef NXNDIALOG_H
#define NXNDIALOG_H

#include <QDialog>
#include <string>
#include "project.h"

namespace Ui {
class NxNDialog;
}

class NxNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NxNDialog(QWidget *parent, int x, int y, int opt,  std::string firstName, std::string secondName);
    ~NxNDialog();

private slots:




private:
    Ui::NxNDialog *ui;

    int xParam;
    int yParam;
    int opt;
    std::string firstName;
    std::string secondName;

};

#endif // NXNDIALOG_H
