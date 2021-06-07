//Неориентированный граф задан в файле в виде списков инцидентных вершин
//Считать его в память. Представление в памяти – в виде массива списков инцидентных вершин.
//Найти все его компоненты связности и сохранить в файл.
//
//Чтение из файла через отдельную абстракцию + валидация

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>

QScopedPointer<QFile>   logFile;
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    logFile.reset(new QFile("logFile.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();
    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(logFile.data());

    switch (type)
    {
    case QtInfoMsg:
        out << "INF ";
        break;
    case QtDebugMsg:
        out << "DBG ";
        break;
    case QtCriticalMsg:
        out << "CRT ";
        break;
    case QtFatalMsg:
        out << "FTL ";
        break;
    default:
        out.flush();
        return;
    }
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    out << context.category << ": "
        << msg << Qt::endl;
    out.flush();
}
