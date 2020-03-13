#include "Amaterasu.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Amaterasu w;
    w.show();

    return a.exec();
}
