#include "calc_new.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calc_new w;
    w.show();

    return a.exec();
}
