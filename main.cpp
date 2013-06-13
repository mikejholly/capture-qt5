#include <iostream>
#include <QCoreApplication>
#include <QtWebKitWidgets>
#include "./Capture.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Capture a web page and save its internal frames in different images" << std::endl << std::endl;
        std::cout << "	Usage: capture <url> <outputfile>" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    QUrl url = QUrl::fromUserInput(QString::fromLatin1(argv[1]));
    QString fileName = QString::fromLatin1(argv[2]);

    QApplication a(argc, argv);
    Capture capture;

    capture.load(url, fileName);

    return a.exec();
}

