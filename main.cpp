#include <QCoreApplication>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, []() {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        // Ví dụ: "2025-04-03 15:47:12"
        qDebug() << timestamp;
    });
    timer.start(500);
    return a.exec();
}
