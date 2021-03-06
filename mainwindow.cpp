#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
#include "minifier.h"
#include "compressor.cpp"
#include "prettifying.cpp"
#include "xml_to_json.h"
#include "check.h"
#include "myhighlighter.h"
#include "correction.h"

QBitArray outputBits(1);
HuffmanNode* root;
//bool compressionMode =false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    errorHighlighter = new myHighlighter(ui->textBrowser->document());
    this->setCentralWidget(ui->groupBox);
    setWindowTitle("XEditora");
    ui->textEdit->setLineWrapMode(QTextEdit::LineWrapMode(0));
    ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(0));
    ui->errorLabel->setHidden(true);

   }


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    inputFieldFile.clear();
    ui->textEdit->setPlainText(QString());
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
         ui->textEdit->setPlainText(text);
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
    QFile file(fileName+"."+fileExtension);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    outputFieldFile = fileName;

    if(outFile.fileType=="txt"){
    }
    else{
    QTextStream out(&file);
    QString text = ui->textBrowser->toPlainText();
    out << text;
    file.close();
    }
}




void MainWindow::on_actionMinify_triggered()
{
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    outFile.fileContent=minify(inFile.fileContent);
    outFile.fileType="xml";
    QString minifyOutput = QString::fromStdString(outFile.fileContent);
    ui->textBrowser->setPlainText(minifyOutput);
}


void MainWindow::on_actionCompress_triggered()
{
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
   ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(1));
    QString fileName = QFileDialog::getSaveFileName(this, "Compress At");
    QFile file(fileName);
    QDir d=QFileInfo(fileName).absoluteFilePath();
     QString absolute=d.absolutePath();
     string strFilePath = absolute.toStdString();
    outputFieldFile = fileName;
    QFile huffmanCodeFile(fileName+"FREQTABLE");
    if (!huffmanCodeFile.open(QFile:: WriteOnly | QFile::Text | QFile::Append)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + huffmanCodeFile.errorString());
        return;
    }
    string str=compress(inFile.fileContent , strFilePath,huffmanCodeFile);
       ui->textBrowser->setPlainText("The File is Compressed in The Choosen Path");
    huffmanCodeFile.close();
}


void MainWindow::on_actionPrettify_triggered()
{
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    outFile.fileContent=prettify(inFile.fileContent);
    outFile.fileType="xml";
    QString prettifyOutput = QString::fromStdString(outFile.fileContent);
    ui->textBrowser->setPlainText(prettifyOutput);
}


void MainWindow::on_actionDecompress_triggered()
{
    std::cout<<"entered decompress";
   QString fileName = QFileDialog::getOpenFileName(this, "Decompress File");
   QDir d=QFileInfo(fileName).absoluteFilePath();
    QString absolute=d.absolutePath();
    string strFilePath = absolute.toStdString();
    std::cout<<strFilePath;
    ui->textBrowser->setPlainText(absolute);

ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(0));
         QFile huffmanCodeFile(fileName+"FREQTABLE");
          if (!huffmanCodeFile.open(QFile::ReadOnly | QFile::Text)) {
              QMessageBox::warning(this, "Warning", "Cannot save file: " + huffmanCodeFile.errorString());
              return;
          }
      string x=decompress(strFilePath, huffmanCodeFile);
      QString view = QString::fromStdString(x);
      ui->textBrowser->setPlainText(view);
            huffmanCodeFile.close();
}


void MainWindow::on_actionConvert_To_JSON_triggered()
{
    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    outFile.fileContent=string_to_json(inFile.fileContent);
    outFile.fileType="json";
    QString conversionOutput = QString::fromStdString(outFile.fileContent);
    ui->textBrowser->setPlainText(conversionOutput);
}


void MainWindow::on_actionCheck_Errors_triggered()
{

    inFile.fileContent=(ui->textEdit->toPlainText()).toStdString();
    inFile.errorFree=true;
    outFile.fileContent=tagCheck(inFile.fileContent,inFile.isChecked,inFile.errorFree,inFile.errorNum);
    outFile.fileType="xml";
    QString checkOutput = QString::fromStdString(outFile.fileContent);
    ui->textBrowser->setPlainText(checkOutput);
    ui->actionPrettify->setEnabled(inFile.isChecked&&inFile.errorFree);
    ui->actionConvert_To_JSON->setEnabled(inFile.isChecked&&inFile.errorFree);
    ui->actionSuggest_Modifications->setEnabled(inFile.isChecked&&!inFile.errorFree);
    ui->errorLabel->setHidden(!(inFile.isChecked&&!inFile.errorFree));
 }


void MainWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText()==""){
        ui->actionCheck_Errors->setEnabled(false);
        ui->errorLabel->setHidden(true);
    }
    else{
        ui->actionCheck_Errors->setEnabled(true);
    }
    inFile.isChecked=false;
    ui->actionPrettify->setEnabled(false);
    ui->actionSuggest_Modifications->setEnabled(false);
    ui->actionConvert_To_JSON->setEnabled(false);
    ui->errorLabel->setHidden(!(inFile.isChecked&&inFile.errorFree));
}




void MainWindow::on_actionSuggest_Modifications_triggered()
{
    ui->textBrowser->setLineWrapMode(QTextEdit::LineWrapMode(0));
    string corrected=correct(inFile.fileContent);
    QString crr=QString::fromStdString(corrected);
    ui->textBrowser->setPlainText(crr);
}

