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
    explicit NxNDialog(QWidget *parent, int x, int y, int opt);
    ~NxNDialog();

private slots:




private:
    Ui::NxNDialog *ui;

    int xParam;
    int yParam;
    int opt;
};

#endif // NXNDIALOG_H
