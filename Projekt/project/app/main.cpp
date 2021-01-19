#include "mainwindow.h"
#include <QApplication>
#include "prepare.h"
#include "levenshteindistance.h"
#include <QDebug>

int main(int argc, char *argv[])
{
//    std::string s = "int int int testowo pisze cos \n //halo \n\n\nss";
//    std::cout << s << std::endl;
//    Prepare p{"../../project/app/cppkeywords.txt"};
//    p.DeleteComments(s);
//    std::cout << s << std::endl;
//    p.removeKeywords(s);
//    std::cout << s << std::endl;
//    p.removeEmptyLines(s);
//    std::cout << s << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
