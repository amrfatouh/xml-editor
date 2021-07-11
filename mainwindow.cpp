#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
#include "minifier.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->groupBox);
    setWindowTitle("XEditora");
    ui->textEdit->setLineWrapMode(QTextEdit::LineWrapMode(0));
    ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(0));
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
}


void MainWindow::on_actionImport_triggered()
{
     QString fileName = QFileDialog::getOpenFileName(this, "Open File");
       QFile file(fileName);
       inputFieldFile = fileName;
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
             QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
             return;
         }
         QTextStream in(&file);
         QString text = in.readAll();
         inFile.fileContent=text.toStdString();
         ui->textEdit->setText(text);
         file.close();


}




void MainWindow::on_actionMove_Output_To_Input_triggered()
{
    ui->textBrowser->selectAll();
    ui->textBrowser->copy();
    ui->textBrowser->clear();
    ui->textEdit->clear();
    ui->textEdit->paste();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    //.xml or .json according to output global var type
    QString fileExtension = QString::fromStdString(outFile.fileType);
    QFile file(fileName+fileExtension);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    outputFieldFile = fileName;

    QTextStream out(&file);

    QString text = ui->textBrowser->toPlainText();
    out << text;
    file.close();
}




void MainWindow::on_actionMinify_triggered()
{
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    outFile.fileContent=minify(inFile.fileContent);
    outFile.fileType="xml";
    QString minifyOutput = QString::fromStdString(outFile.fileContent);
    ui->textBrowser->setText(minifyOutput);
}

