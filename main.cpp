#include "mainwindow.h"
#include <QApplication>
#include "classes.cpp"

InputFile inFile;
OutputFile outFile;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
