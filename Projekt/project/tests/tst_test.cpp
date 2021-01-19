#include <QtTest>

// add necessary includes here
#include "prepare.h"

class Test : public QObject
{
    Q_OBJECT

private slots:

    void test_removeEmptyLines()
    {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="\n\n\nDzien dobry\nHello World!\n\n\n\n\nLorem ipsum\n\nTest\n\n\n";
        std::string sout="Dzien dobry\nHello World!\nLorem ipsum\nTest\n";

        p.removeEmptyLines(sin);
        QVERIFY(sin==sout);
    }
    void test_removeKeywords()
    {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="avcreturnintforxDwhiletruefalsetrycatchcaseswitch123 break;";
        std::string sout="avcxD123 ;";

        p.removeKeywords(sin);
        QVERIFY(sin==sout);
    }
     void test_DeleteComments()
     {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="//komentarz w pliku\nLorem ipsum\nDzien dobry, macie ta Colke jeszcze?\nStanooooskiiiiiii\n/*tu jest komentarz\ngagas\nabababa*/\nDalej tekst";
        std::string sout="\nLorem ipsum\nDzien dobry, macie ta Colke jeszcze?\nStanooooskiiiiiii\n\nDalej tekst";

        p.DeleteComments(sin);
        QVERIFY(sin==sout);
     }

     void test_ConstructorTest()
     {
         Prepare p{"../../project/app/cppkeywords.txt"};
         QVERIFY(p.keywords.empty()==false);
         QVERIFY(p.keywords.size()==63);
     }
};


QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
