#ifndef NXNDIALOG_H
#define NXNDIALOG_H

#include <QDialog>

namespace Ui {
class NxNDialog;
}

class NxNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NxNDialog(QWidget *parent = nullptr);
    ~NxNDialog();

private slots:


private:
    Ui::NxNDialog *ui;
};

#endif // NXNDIALOG_H
