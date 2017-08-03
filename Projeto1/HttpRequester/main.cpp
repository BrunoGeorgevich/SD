#include <QCoreApplication>

#include "requester.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Requester *requester = new Requester();

    return a.exec();
}
