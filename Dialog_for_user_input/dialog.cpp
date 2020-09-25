#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setLabelData(QString str, QStringList pre, QStringList input, QString type)
{
    ui->label_dialog_status->setText(str);
    this->pre = pre;
    this->input = input;
    this->type = type;

}

void Dialog::on_pushButton_cance_clicked()
{
    this->close();
}

QStringList Dialog::findWord(QString sentence)
{
    QStringList list = sentence.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);

//    for(int i = 0; i < list.size(); i++){
//        qDebug() << "Find word " << list[i];
//    }
    return list;
}

void Dialog::on_pushButton_done_clicked()
{
//    qDebug() << "Word algorightm = " << pre.size() << " " << post.size() ;

    int wrong_word_counter = 0;

    if(pre.size() == post.size()){
        for(int i = 0; i < pre.size(); i++){
            if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) != 0){
    //            qDebug() << "Wrong words " << post[i];
                post[i] = "<u>"+post[i]+"</u>";
                ++wrong_word_counter;
            }
        }
    }else if(pre.size() <= post.size()){
        for(int i = 0; i < pre.size(); i++){
            if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) != 0){
    //            qDebug() << "Wrong words " << post[i];
                post[i] = "<u>"+post[i]+"</u>";
                ++wrong_word_counter;
            }
        }
    }else if(pre.size() >= post.size()){
        for(int i = 0; i < post.size(); i++){
            if(QString::compare(pre[i], post[i], Qt::CaseInsensitive) != 0){
    //            qDebug() << "Wrong words " << post[i];
                post[i] = "<u>"+post[i]+"</u>";
                ++wrong_word_counter;
            }
        }
    }


//    emit banglaResultSendToMain(input, output, wrong_word_counter, this->type);
    emit banglaResultSendToMain(pre, post, wrong_word_counter, this->type);
    input.clear();
    output.clear();
    type = "";
    pre.clear();
    post.clear();
    this->close();
}

void Dialog::on_pushButton_word_input_clicked()
{
    post.clear();
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Enter a text file"),
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
        QStringList lis = findWord(line);
        output.append(line);
        for(int i = 0; i < lis.size(); i++){
            post.append(lis[i]);
        }
    }
    file.close();
}
