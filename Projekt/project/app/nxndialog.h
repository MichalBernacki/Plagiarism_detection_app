#ifndef NXNDIALOG_H
#define NXNDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class NxNDialog;
}

class NxNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NxNDialog(QWidget *parent, int x, int y, int opt, std::string firstName );
    ~NxNDialog();

private slots:




private:
    Ui::NxNDialog *ui;

    int xParam;
    int yParam;
    int opt;
    std::string firstName;
};

#endif // NXNDIALOG_H
