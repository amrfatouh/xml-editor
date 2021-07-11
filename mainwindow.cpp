#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->groupBox);
    ui->textEdit->setFontPointSize(14);
    ui->textBrowser->setFontPointSize(14);
    ui->textEdit->setLineWrapMode(QTextEdit::LineWrapMode(0));
   }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    inputFieldFile.clear();
    ui->textEdit->setText(QString());
    ui->textBrowser->clear();
    ui->textEdit->setFontPointSize(14);
    ui->textBrowser->setFontPointSize(14);

}


void MainWindow::on_actionImport_triggered()
{
     QString fileName = QFileDialog::getOpenFileName(this, "Open The File");
       QFile file(fileName);
       inputFieldFile = fileName;
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
             QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
             return;
         }
         setWindowTitle(fileName);
         QTextStream in(&file);
         QString text = in.readAll();
         ui->textEdit->setText(text);
         file.close();
         ui->textEdit->selectAll();
         ui->textEdit->setFontPointSize(14);

}



