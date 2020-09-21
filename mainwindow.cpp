#include "mainwindow.h"
#include "ui_mainwindow.h"

#define OUT 0
#define IN 1
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned MainWindow::wordCount(QString sentence)
{
    QByteArray ba = sentence.toLocal8Bit();
    char *str = ba.data();

    int state = OUT;
    unsigned wc = 0; // word count

    // Scan all characters one by one
    while (*str)
    {
        // If next character is a separator, set the
        // state as OUT
        if (*str == ' ' || *str == '\n' || *str == '\t')
            state = OUT;

        // If next character is not a word separator and
        // state is OUT, then set the state as IN and
        // increment word count
        else if (state == OUT)
        {
            state = IN;
            ++wc;
        }

        // Move to next character
        ++str;
    }
    return wc;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Enter question file"),
                "C//",
                "Text File (*.txt)"
                );
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0,"info",file.errorString());
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        pre.append(line);
        //        qDebug() << "Line = " << line.size();
    }
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Enter your file"),
                "C//",
                "Text File (*.txt)"
                );
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0,"info",file.errorString());
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        post.append(line);
        //        qDebug() << "Line = " << line.size();
    }
    file.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(pre.size() != 0 && post.size() != 0){
        for (int i = 0; i < pre.size(); i++){

            if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) == 0){
                unsigned pr = wordCount(pre[i]);
                unsigned po = wordCount(post[i]);

                qDebug() << pre[i] << " pre " << pr << " po " << po;
            }

        }
    }
    pre.clear();post.clear();

}
