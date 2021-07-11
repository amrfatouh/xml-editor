#include "mainwindow.h"
#include "ui_mainwindow.h"

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
     QString fileName = QFileDialog::getOpenFileName(this, "Open The File");
       QFile file(fileName);
       inputFieldFile = fileName;
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
             QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
             return;
         }
         QTextStream in(&file);
         QString text = in.readAll();
         ui->textEdit->setText(text);
         file.close();
//         ui->textEdit->selectAll();
//         ui->textEdit->setFontPointSize(14);

}




void MainWindow::on_actionMove_Output_To_Input_triggered()
{
    ui->textBrowser->selectAll();
    ui->textBrowser->cut();
    ui->textEdit->clear();
    ui->textEdit->paste();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    QFile file(fileName+".xml");

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    inputFieldFile = fileName;

    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
      QFile file(fileName);
      if (!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
          return;
      }
      inputFieldFile = fileName;
      setWindowTitle(fileName);
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText();
      out << text;
      file.close();
}

