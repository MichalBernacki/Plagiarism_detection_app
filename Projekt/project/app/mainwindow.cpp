#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levenshteindistance.h"
#include "simplealg.h"
#include "prepare.h"
#include "utils.h"
#include <iostream>
#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QColor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto stateMachine = new QStateMachine{this};

    //ALL STATES
    auto stateStartup = new QState(stateMachine);
    auto stateOpen = new QState{stateMachine};
    auto stateError = new QState{stateMachine};
    auto stateView = new QState{stateMachine};
    auto stateChoose = new QState{stateMachine};
    auto stateCompare = new QState{stateMachine};
    auto stateShow = new QState{stateMachine};
    auto stateClear = new QState{stateMachine};
    //STARTUP
    stateStartup->assignProperty(ui->pbStart, "text", "Start");
    stateStartup->assignProperty(ui->pbOpen, "enabled", true);
    stateStartup->assignProperty(ui->pbStart, "enabled", false);
    stateStartup->assignProperty(ui->taCompare, "enabled", false);
    stateStartup->assignProperty(ui->leLabel, "text", "Load directory to start...");
    stateStartup->assignProperty(ui->cbBox1, "enabled", false);
    stateStartup->assignProperty(ui->cbBox2, "enabled", false);
    stateStartup->assignProperty(ui->cbBox3, "enabled", false);
    stateStartup->assignProperty(ui->cbBox4, "enabled", false);
    stateStartup->assignProperty(ui->cbBox5, "enabled", false);
    stateStartup->assignProperty(ui->frResult, "enabled", false);
    stateStartup->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateStartup->assignProperty(ui->pbClear, "enabled", false);
    stateStartup->assignProperty(ui->pbFileM1, "enabled", false);
    //OPEN
    connect(stateOpen, SIGNAL(entered()), this, SLOT(open()));
    stateOpen->addTransition(this, SIGNAL(error(QString)), stateError);
    connect(this, SIGNAL(error(QString)), this, SLOT(errorFunction(QString)));
    stateOpen->addTransition(this, SIGNAL(opened()), stateView);
    stateOpen->assignProperty(ui->pbStart, "text", "Start");

    //ERROR
    stateError->assignProperty(ui->pbOpen, "enabled", true);
    stateError->assignProperty(ui->pbStart, "enabled", false);
    stateError->assignProperty(ui->cbBox1, "enabled", false);
    stateError->assignProperty(ui->cbBox2, "enabled", false);
    stateError->assignProperty(ui->cbBox3, "enabled", false);
    stateError->assignProperty(ui->cbBox4, "enabled", false);
    stateError->assignProperty(ui->cbBox5, "enabled", false);
    stateError->assignProperty(ui->taCompare, "enabled", false);
    stateError->assignProperty(ui->pbClear, "enabled", false);

    stateError->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //VIEW
    connect(stateView, SIGNAL(entered()), this, SLOT(view()));
    stateView->assignProperty(ui->pbOpen, "enabled", true);
    stateView->assignProperty(ui->pbStart, "enabled", true);
    stateView->assignProperty(ui->pbStart, "text", "Start");
    stateView->assignProperty(ui->taCompare, "enabled", false);
    stateView->assignProperty(ui->cbBox1, "enabled", true);
    stateView->assignProperty(ui->cbBox2, "enabled", true);
    stateView->assignProperty(ui->cbBox3, "enabled", true);
    stateView->assignProperty(ui->cbBox4, "enabled", true);
    stateView->assignProperty(ui->cbBox5, "enabled", true);
    stateView->assignProperty(ui->frResult, "enabled", false);

    stateView->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateChoose);
    stateView->addTransition(ui->pbClear,SIGNAL(clicked(bool)),stateClear);

    //stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateShow);


    //CHOOSE
    connect(stateChoose, SIGNAL(entered()), this, SLOT(checkChoose()));
    stateChoose->addTransition(this, SIGNAL(mustChoose()), stateView);
    stateChoose->addTransition(this, SIGNAL(choosed()), stateCompare);


    //COMPARE
    stateCompare->assignProperty(ui->taCompare, "enabled", true);
    connect(stateCompare, SIGNAL(entered()), this, SLOT(compare()));
    //stateCompare->addTransition(this, SIGNAL(error(QString)), stateError);
    //connect(ui->taCompare->horizontalHeader(), SIGNAL(sectionClicked()), this, SLOT(Table_HeaderClick()) );
    stateCompare->addTransition(ui->pbClear,SIGNAL(clicked(bool)),stateClear);
    stateCompare->addTransition(ui->pbStart,SIGNAL(clicked(bool)),stateView);
    stateCompare->addTransition(ui->taCompare, SIGNAL(cellClicked(int, int)), stateShow );
    connect(ui->taCompare, SIGNAL(cellClicked(int, int)), this, SLOT(onTableClicked(int, int)) );
    stateCompare->assignProperty(ui->pbOpen,"enabled",false);
    stateCompare->assignProperty(ui->pbStart, "enabled", true);
    stateCompare->assignProperty(ui->cbBox1, "enabled", false);
    stateCompare->assignProperty(ui->cbBox2, "enabled", false);
    stateCompare->assignProperty(ui->cbBox3, "enabled", false);
    stateCompare->assignProperty(ui->cbBox4, "enabled", false);
    stateCompare->assignProperty(ui->cbBox5, "enabled", false);
    stateCompare->assignProperty(ui->pbClear, "enabled", true);

    //CLEAR
    connect(stateClear, SIGNAL(entered()), this, SLOT(clear()));
    stateClear->addTransition(this,SIGNAL(cleared()),stateStartup);


    //SHOW

    connect(ui->lwResults, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListElemClicked(QListWidgetItem*)));

    connect(ui->pbFileM1, SIGNAL(clicked()), this, SLOT(showResultsInPanel()));
    stateShow->assignProperty(ui->pbStart, "text", "Return");
    stateShow->assignProperty(ui->frResult, "enabled", true);
    stateShow->addTransition(ui->pbClear,SIGNAL(clicked(bool)),stateClear);
    stateShow->addTransition(ui->pbStart,SIGNAL(clicked(bool)),stateView);
    stateShow->assignProperty(ui->pbClear, "enabled", true);

    stateMachine->setInitialState(stateStartup);
    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){
    QFileDialog w;
    w.setFileMode(QFileDialog::DirectoryOnly);
    w.setOption(QFileDialog::DontUseNativeDialog,true);
    //w.setOption(QFileDialog::ShowDirsOnly,false); //Decide whether we want to see other files, more intuitive navigation, weird selection "quirks"

    QListView *lView = w.findChild<QListView*>("listView");
    if (lView)
        lView->setSelectionMode(QAbstractItemView::MultiSelection);
    QTreeView *tView = w.findChild<QTreeView*>();
    if (tView)
        tView->setSelectionMode(QAbstractItemView::MultiSelection);

    if(w.exec() == 0){
        emit opened();  //User canceled
        return;
    }

    //1. Just gets a single directory, simple, no complications
    //QString filepath = QFileDialog::getExistingDirectory(this, tr("Open directory"), "..", QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog);

    //2. Able to select multiple paths, shows other files (but can also choose them, so Project::ctor just ignores them)
    for(auto& filepath: w.selectedFiles()){
        try {
            projects.emplace(filepath.toStdString());
        }catch(const NotADirectory& e){
            std::cerr<<e.what()<<'\n';//best to just ignore it
            return;
        }
        catch (const std::exception& e) {
            emit error(e.what()); //emit error with particular string as a message in message box
            return;
        }
    }
    emit opened();
}

void MainWindow::checkChoose(){
    if( !(ui->cbBox1->isChecked() || ui->cbBox2->isChecked()))
    {
        QMessageBox msgBox;
        msgBox.setText("You have to choose at least 1 algorithm!");
        msgBox.exec();
        emit mustChoose();
    }
    else
        emit choosed();
}

void MainWindow::errorFunction(QString info){
    QString errorMsg = "Program error\n\n" + info +"\n";
    QMessageBox::information( this, "Error", errorMsg, QMessageBox::Ok );
    std::cerr << errorMsg.toStdString();
    std::cerr << "\n";
}


void MainWindow::clear(){
    ui->taCompare->clear();
    projects.clear();
    emit cleared();
}


void MainWindow::compare(){
    int l = 0;
    int k = 0;

    results.clear();
    results.resize(projects.size()*projects.size());

    for (auto& project1:projects)
    {
        for(auto& project2:projects)
        {
            if(k==l)
            {
                k++;
                continue;
            }
            Result levenshteinRes {"Levenshtein"};
            Result simpleAlgRes {"SimpleAlg"};

            float percent = 0;
            float num_of_cmp = 0;

            auto& p1 = project1.GetFiles();
            auto& p2 = project2.GetFiles();
            for(auto& file1: p1){
                for(auto& file2: p2)
                {
                    std::string s1=file1.m_OriginalContent;
                    std::string s2=file2.m_OriginalContent;
                    Prepare p{"../../project/app/cppkeywords.txt"};
                    if(ui->cbBox5->isChecked())
                    {
                        //komentarze
                        p.DeleteComments(s1);
                        p.DeleteComments(s2);
                    }
                    if(ui->cbBox3->isChecked())
                    {
                        //slowa kluczowe
                       p.removeKeywords(s1);
                       p.removeKeywords(s2);
                    }

                    if(ui->cbBox4->isChecked())
                    {
                        //puste linie
                        p.removeEmptyLines(s1);
                        p.removeEmptyLines(s2);
                    }

                    if(ui->cbBox1->isChecked())
                    {
                        num_of_cmp++;
                        LevenshteinDistance l{};
                        float res = l.compare(s1,s2);
                        if(res > levenshteinRes.bestMatchValue){
                            levenshteinRes.bestMatchValue = res;
                            levenshteinRes.bestMatch1 = &file1;
                            levenshteinRes.bestMatch2 = &file2;
                        }
                        levenshteinRes.value +=res;
                        percent+=res;
                    }
                    if(ui->cbBox2->isChecked())
                    {
                        num_of_cmp++;
                        SimpleAlg l{};
                        float res = l.compare(s1,s2);
                        if(res > simpleAlgRes.bestMatchValue){
                            simpleAlgRes.bestMatchValue = res;
                            simpleAlgRes.bestMatch1 = &file1;
                            simpleAlgRes.bestMatch2 = &file2;
                        }
                        simpleAlgRes.value += res;
                        percent+=res;
                    }
                }
            }
            percent/=num_of_cmp;

            levenshteinRes.value /= p1.size()*p2.size();
            simpleAlgRes.value /= p1.size()*p2.size();
            if(ui->cbBox1->isChecked()) results.at(l*projects.size() + k).push_back(levenshteinRes);
            if(ui->cbBox2->isChecked()) results.at(l*projects.size() + k).push_back(simpleAlgRes);

            QTableWidgetItem *item = ui->taCompare->item(l,k);
            item= new QTableWidgetItem();
            ui->taCompare->setItem(l,k,item);
            item->setText(QString::number(percent*100)+"%");
            item->setBackground(QColor(255*percent,255-255*percent,0,255));
            k++;
        }
        k=0;
        l++;
    }
    ui->retranslateUi(this);
    ui->pbStart->setText("Return");
}



void MainWindow::view()
{
    ui->taCompare->clear();
    ui->taCompare->setRowCount(projects.size());
    ui->taCompare->setColumnCount(projects.size());

    ui->taCompare->horizontalHeader()->setDefaultSectionSize(160);  //width
    ui->taCompare->verticalHeader()->setDefaultSectionSize(90);     //height  -> Size of cell below
    size_t r = 0;
    for (auto& project:projects)
    {
        ui->taCompare->setHorizontalHeaderItem(r, new QTableWidgetItem(project.GetName().c_str()));
        ui->taCompare->setVerticalHeaderItem(r, new QTableWidgetItem(project.GetName().c_str()));

        ++r;
    }
}

void MainWindow::showResultsInPanel()
{
    ndial = new NxNDialog(this, xParam, yParam,  results[yParam*projects.size() + xParam][resultIndex]);
    ndial->setModal(true);
    ndial->exec();
}
void MainWindow::onTableClicked(int y, int x )
{
    this->xParam = x;
    this->yParam = y;
    ui->lwResults->clear();
    ui->pbFileM1->setEnabled(false);
    for(auto& result: results.at(y*projects.size() + x)){
        std::string resultString = result.algorithmName + ": ";
        resultString += std::to_string(result.value * 100);
        ui->lwResults->addItem(QString::fromStdString(resultString));
    }
}
void MainWindow::onListElemClicked(QListWidgetItem *item)
{
    this->resultIndex =  ui->lwResults->selectionModel()->currentIndex().row();
    ui->pbFileM1->setEnabled("true");
}
