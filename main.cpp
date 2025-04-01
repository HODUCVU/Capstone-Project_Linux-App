#include "testing.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Testing testing;
    testing.start();
    return a.exec();
}
