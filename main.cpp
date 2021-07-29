#include "mainwindow.h"
#include <QApplication>
#include "classes.cpp"

InputFile inFile = InputFile();
OutputFile outFile = OutputFile();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
