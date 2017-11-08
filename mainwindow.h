#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QIcon>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void getTranslation();
    void onTranslationRecieved(QNetworkReply* reply);

private:
    QRadioButton *rb_nte;
    QRadioButton *rb_etn;
    QPushButton *b_translate;
    QTextEdit *te_input;
    QTextEdit *te_output;
    QLabel *l_about;
};

#endif
