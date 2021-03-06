#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QBitArray>
#include <QSyntaxHighlighter>
#include "myhighlighter.h"
#include <QRegExp>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionImport_triggered();

    void on_actionMove_Output_To_Input_triggered();

    void on_actionSave_As_triggered();

    void on_actionMinify_triggered();

    void on_actionCompress_triggered();

    void on_actionPrettify_triggered();


    void on_actionConvert_To_JSON_triggered();

    void on_actionCheck_Errors_triggered();

    void on_textEdit_textChanged();




    void on_actionDecompress_triggered();

    void on_actionSuggest_Modifications_triggered();

private:
    Ui::MainWindow *ui;
    QString inputFieldFile = "";
    QString outputFieldFile = "";
    myHighlighter *errorHighlighter;
};
#endif // MAINWINDOW_H
