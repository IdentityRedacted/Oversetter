#include "mainwindow.h"

MainWindow::MainWindow() : QWidget()
{
    setFixedSize(300, 400);
    setFont(QFont("Calibri", 14));
    QPalette p = palette();
    p.setColor(QPalette::Background, Qt::white);
    setPalette(p);
    setWindowIcon(QIcon("icon.png")); // Icon by Freepik

    rb_nte = new QRadioButton("Norsk til Engelsk", this); // Norwegian to English
    rb_nte->setGeometry(10, 10, 190, 30);
    rb_nte->setChecked(true);

    rb_etn = new QRadioButton("English to Norwegian", this);
    rb_etn->setGeometry(10, 40, 190, 30);

    b_translate = new QPushButton("Oversette\nTranslate", this);
    b_translate->setCursor(Qt::PointingHandCursor);
    b_translate->setGeometry(200, 10, 90, 60);

    te_input = new QTextEdit("[Inngang]", this);
    te_input->setGeometry(10, 80, 280, 130);

    te_output = new QTextEdit("[Output]", this);
    te_output->setGeometry(10, 220, 280, 130);
    te_output->setReadOnly(true);

    l_about = new QLabel("Drevet av Google Oversetter.\nForfatter: Rémi DUJARDIN    Versjon: 1.3", this); // Powered by Google Translate. Author: Rémi DUJARDIN Version: 1.3
    l_about->setGeometry(10, 360, 280, 30);
    l_about->setFont(QFont("Calibri", 10));
    l_about->setAlignment(Qt::AlignCenter);

    QObject::connect(b_translate, SIGNAL(clicked()), this, SLOT(getTranslation()));
}

void MainWindow::getTranslation()
{
    te_output->setText("[Oversettelse pågår]\n[Translation in progress]");

    // Buind the URL
    QString url = "http://translate.googleapis.com/translate_a/single?client=gtx";
    if (rb_nte->isChecked())
    {
        url.append("&sl=no&tl=en&dt=t&q=");
    }
    else
    {
        url.append("&sl=en&tl=no&dt=t&q=");
    }
    url.append(te_input->toPlainText());
    qInfo() << "url: " + url;

    // Make an HTTP request
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onTranslationRecieved(QNetworkReply*)));
    nam->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::onTranslationRecieved(QNetworkReply* reply)
{
    // Parse the response
    QString content = (QString) reply->readAll();
    qInfo() << "content: " + content;
    QScriptEngine engine;
    QScriptValue result = engine.evaluate(content);
    QString translation = result.property("0").property("0").property("0").toString();

    // Display the translation
    te_output->setText(translation);
}
