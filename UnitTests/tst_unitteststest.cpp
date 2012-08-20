#include <QString>
#include <QtTest>

class UnitTestsTest : public QObject
{
    Q_OBJECT
    
public:
    UnitTestsTest();
    
private Q_SLOTS:
    void testCase1();
};

UnitTestsTest::UnitTestsTest()
{
}

void UnitTestsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
