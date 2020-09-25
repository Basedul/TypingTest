#include "mainwindow.h"
#include "ui_mainwindow.h"

#define OUT 0
#define IN 1
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    user_input_dialog = new Dialog();
    connect(user_input_dialog, SIGNAL(banglaResultSendToMain(QStringList, QStringList, int, QString)), this, SLOT(banglaResultInToMain(QStringList, QStringList, int, QString)));
}

MainWindow::~MainWindow()
{
    delete user_input_dialog;
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

QStringList MainWindow::findWord(QString sentence)
{
    QStringList list = sentence.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);

    //    for(int i = 0; i < list.size(); i++){
    //        qDebug() << "Find word " << list[i];
    //    }
    return list;
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

        //        pre.append(line);
        QStringList lis = findWord(line);
        for(int i = 0; i < lis.size(); i++){
            pre.append(lis[i]);
        }
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
        //        post.append(line);
        //        qDebug() << "Line = " << line.size();
        QStringList lis = findWord(line);
        for(int i = 0; i < lis.size(); i++){
            post.append(lis[i]);
        }
    }
    file.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "Total words " << pre.size();

    int wrong_word_counter = 0;

    //    if(pre.size() == post.size()){

    //    }else if(pre.size() >)

    for(int i = 0; i < pre.size(); i++){
        if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) != 0){
            //            qDebug() << "Wrong words " << post[i];
            ++wrong_word_counter;
        }
    }

    //    if(pre.size() != 0 && post.size() != 0){
    //        //        align=justify
    //        QString html =
    //                "<div align=left>"
    //                "Sender Name<br>"
    //                "street 34/56A<br>"
    //                "121-43 city"
    //                "</div>"
    //                "<h1 align=center>DOCUMENT TITLE</h1>"
    //                "<p >";
    //        for (int i = 0; i < pre.size(); i++){

    //            if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) == 0){
    //                unsigned pr = wordCount(pre[i]);
    //                unsigned po = wordCount(post[i]);

    //                //                qDebug() << pre[i] << " pre " << pr << " po " << po;
    //                qDebug() << post[i];
    //                html.append(post[i]);

    //            }

    //        }
    //        html.append("</p>");
    //        html.append("<div align=right>sincerly</div>");

    //        QTextDocument document;
    //        //                document.setPlainText(html);
    //        document.setHtml(html);

    //        QPrinter printer(QPrinter::PrinterResolution);
    //        printer.setOutputFormat(QPrinter::PdfFormat);
    //        printer.setPaperSize(QPrinter::A4);
    //        printer.setOutputFileName("./test.pdf");
    //        printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    //        document.print(&printer);
    //    }
    //    pre.clear();post.clear();

}

void MainWindow::on_pushButton_print_clicked()
{

}

void MainWindow::on_pushButton_bangla_clicked()
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
    QStringList pre1, input;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        input.append(line);
        //        pre.append(line);
        QStringList lis = findWord(line);
        for(int i = 0; i < lis.size(); i++){
            pre1.append(lis[i]);
        }
        //        qDebug() << "Line = " << line.size();
    }
    file.close();
    user_input_dialog->setLabelData("বাংলার জন্য ইনপুট ফাইল সিলেক্ট করুন", pre1, input, "Bangla");
    user_input_dialog->exec();
}

void MainWindow::banglaResultInToMain(QStringList input, QStringList output, int ww, QString type)
{
    qDebug() << "iput .size = " << input.size();
    QString html =
            "<div align=left>"
            "Name: "+ui->lineEdit_name->text()+"<br>"
            "ID: "+ui->lineEdit_id->text()+"<br>"
            "BIAM Foundation"
            "</div>"
            "<h1 align=center>Typing Test for "+type+"</h1>";
    html.append("<div align=left>");
    html.append("<p >");
    html.append("<h1 align=left>Input text:</h1>");
    for(int i = 0; i < input.size(); i++){
//        qDebug() << input[i];
        html.append(input[i]+" ");
    }
    html.append("</p>");
    html.append("</div>");
    html.append("<div align=left>");
    html.append("<p >");
    html.append("<h1 align=left>Output text:</h1>");
    for(int i = 0; i < output.size(); i++){
        html.append(output[i]+" ");
    }
    html.append("</p>");
    html.append("</div>");
//    html.append("<div align=right>sincerly</div>");

    html.append("<div align=left>");
    html.append("<p >");
    html.append("<h1 align=left>Result:</h1>");

//    html.append("Number of valid words: "+QString::number((output.size()-ww))+" and invalid words: "+QString::number(ww));
    if(input.size() == output.size()){
        int res = input.size() - output.size();
        int res1 = input.size() - res;
        html.append("Total Words: "+QString::number(input.size())+", Number of valid words: "+QString::number((res1-ww))+" and invalid words: "+QString::number(ww));
    }
    else if(input.size() >= output.size()){
        int res = input.size() - output.size();
        int res1 = input.size() - res;
        html.append("Total Words: "+QString::number(input.size())+", Number of valid words: "+QString::number((res1-ww))+" and invalid words: "+QString::number(ww));
    }else if(input.size() <= output.size()){
        int res = output.size() - input.size();
        int res1 = output.size() - res;
        html.append("Total Words: "+QString::number(input.size())+", Number of valid words: "+QString::number((res1-ww))+" and invalid words: "+QString::number(ww));
    }

    html.append("</p>");
    html.append("</div>");
    html.append("<div align=right>Signature</div>");

    QTextDocument document;
    //                document.setPlainText(html);
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
//    printer.setOutputFileName("./test.pdf");
    QDir dir("./"+ui->lineEdit_id->text());
    if (!dir.exists())
        dir.mkpath(".");
//        dir.mkpath("./"+ui->lineEdit_id->text());
    printer.setOutputFileName("./"+ui->lineEdit_id->text()+"/"+type+".pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);

    pre.clear();
    post.clear();
}

void MainWindow::on_pushButton_english_clicked()
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
    QStringList pre1, input;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        input.append(line);
        //        pre.append(line);
        QStringList lis = findWord(line);
        for(int i = 0; i < lis.size(); i++){
            pre1.append(lis[i]);
        }
        //        qDebug() << "Line = " << line.size();
    }
    file.close();
    user_input_dialog->setLabelData("ইংলিশের জন্য ইনপুট ফাইল সিলেক্ট করুন", pre1, input, "English");
    user_input_dialog->exec();
}
