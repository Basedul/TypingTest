#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QTextDocument>
#include <QPrinter>
#include <Dialog_for_user_input/dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    unsigned wordCount(QString);
    QStringList findWord(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_bangla_clicked();
    void on_pushButton_english_clicked();

public slots:
    void banglaResultInToMain(QStringList, QStringList, int, QString);

private:
    Ui::MainWindow *ui;
    QStringList pre, post;
    Dialog *user_input_dialog;
};

#endif // MAINWINDOW_H
