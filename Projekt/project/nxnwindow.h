#ifndef NXNWINDOW_H
#define NXNWINDOW_H

#include <QMainWindow>

namespace Ui {
class NxNWindow;
}

class NxNWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NxNWindow(QWidget *parent = nullptr);
    ~NxNWindow();

private:
    Ui::NxNWindow *ui;
};

#endif // NXNWINDOW_H
