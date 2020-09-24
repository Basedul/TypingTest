#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QTextDocument>
#include <QPrinter>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setLabelData(QString, QStringList, QStringList, QString);
    QStringList findWord(QString);

private slots:
    void on_pushButton_cance_clicked();

    void on_pushButton_done_clicked();
    void on_pushButton_word_input_clicked();

signals:
    void banglaResultSendToMain(QStringList, QStringList, int, QString);


private:
    Ui::Dialog *ui;
    QStringList pre, post, input, output;
    QString type;
};

#endif // DIALOG_H
