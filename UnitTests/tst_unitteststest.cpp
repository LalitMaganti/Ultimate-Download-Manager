#include <QString>
#include <QtTest>
#include "downloadfile.h"

class UnitTestsTest : public QObject
{
    Q_OBJECT
    
public:
    UnitTestsTest();
    
private Q_SLOTS:
    void testTime();
};

UnitTestsTest::UnitTestsTest()
{
}

void UnitTestsTest::testTime()
{
    /*QString k =   "9400K ,,,,,,,,,, ,,,,,,,,,, ,,,,,,,,,. .......... ..........  9%  493K 7m46s";
    WgetProcess wp;
    //wp.processProgress(&k);
    const QString l = wp.progressObject.time;
    const QString g = "7 minutes 46 seconds";
    QCOMPARE(l, g);*/
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
