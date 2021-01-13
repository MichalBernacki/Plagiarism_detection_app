#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto stateMachine = new QStateMachine{this};

    //Locked state
    auto stateUnLocked = new QState(stateMachine);
    stateUnLocked->assignProperty(ui->pbToggle, "text", "Lock");
    stateUnLocked->assignProperty(ui->pbOpen, "enabled", true);
    stateUnLocked->assignProperty(ui->pbSave, "enabled", true);
    stateUnLocked->assignProperty(ui->teText, "enabled", true);

    //Lock State
    auto stateLocked = new QState(stateMachine);
    stateLocked->assignProperty(ui->pbToggle, "text", "Unlock");
    stateLocked->assignProperty(ui->pbOpen, "enabled", false);
    stateLocked->assignProperty(ui->pbSave, "enabled", false);
    stateLocked->assignProperty(ui->teText, "enabled", false);

    //Startup State
    auto stateStartup = new QState{stateUnLocked};
    stateStartup->assignProperty(ui->pbOpen, "enabled", true);
    stateStartup->assignProperty(ui->pbSave, "enabled", false);
    stateStartup->assignProperty(ui->teText, "enabled", false);
    stateStartup->assignProperty(ui->teText, "placeholderText", "Open file to start editing...");

    auto stateOpen = new QState{stateUnLocked};

    //Error State
    auto stateError = new QState{stateUnLocked};
    stateError->assignProperty(ui->pbOpen, "enabled", true);
    stateError->assignProperty(ui->pbSave, "enabled", false);
    stateError->assignProperty(ui->teText, "enabled", false);
    stateError->assignProperty(ui->teText, "placeholderText", "Error ocured. Open file to start editing...");

    //View State
    auto stateView = new QState{stateUnLocked};
    stateView->assignProperty(ui->pbOpen, "enabled", true);
    stateView->assignProperty(ui->pbSave, "enabled", false);
    stateView->assignProperty(ui->teText, "enabled", true);

    //Edit State
    auto stateEdit = new QState{stateUnLocked};
    stateEdit->assignProperty(ui->pbOpen, "enabled", false);
    stateEdit->assignProperty(ui->pbSave, "enabled", true);
    stateEdit->assignProperty(ui->teText, "enabled", true);

    auto stateSave = new QState{stateUnLocked};

    QHistoryState *stateHistory = new QHistoryState(stateUnLocked);
    stateHistory->setDefaultState(stateStartup);

    //Transation for lock and unlock
    stateUnLocked->addTransition(ui->pbToggle, SIGNAL(clicked()), stateLocked);
    stateLocked->addTransition(ui->pbToggle, SIGNAL(clicked()), stateHistory);


    //Simple transition
    stateStartup->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateError->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->teText, SIGNAL(textChanged()), stateEdit);
    stateEdit->addTransition(ui->pbSave, SIGNAL(clicked()), stateSave);


    //Open transition
    connect(stateOpen, SIGNAL(entered()), this, SLOT(open()));
    stateOpen->addTransition(this, SIGNAL(opened()), stateView);
    stateOpen->addTransition(this, SIGNAL(error()), stateError);

    //Save transition
    connect(stateSave, SIGNAL(entered()), this, SLOT(save()));
    stateSave->addTransition(this, SIGNAL(saved()), stateView);
    stateSave->addTransition(this, SIGNAL(error()), stateError);


    //Init state machine
    stateUnLocked->setInitialState(stateStartup);
    stateMachine->setInitialState(stateUnLocked);
    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    fileName = QFileDialog::getOpenFileName(this, "open a file", QDir::currentPath());
    QFile file(fileName);

    if( !file.open(QFile::ReadOnly | QFile::Text)){
        ui->teText->setPlainText("");
        emit error();
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->teText->setPlainText(text);
    file.close();

    emit opened();
}

void MainWindow::save()
{
    QFile file(fileName);

    if( !file.open(QFile::WriteOnly | QFile::Text)){
        ui->teText->setPlainText("");
        emit error();
        return;
    }

    QTextStream out(&file);
    QString text = ui->teText->toPlainText();
    out << text;
    file.flush();
    file.close();

    emit saved();
}
