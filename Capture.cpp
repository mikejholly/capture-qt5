#include "./Capture.hpp"
#include <QTimer>

Capture::Capture()
{
    connect(&page, &QWebPage::loadFinished, this, &Capture::loadFinished);
}

void Capture::load(const QUrl &url, const QString &outputFileName)
{
    int index = outputFileName.lastIndexOf('.');
    fileName = (index == -1) ? outputFileName + ".png" : outputFileName;

    page.mainFrame()->load(url);
    page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    page.setViewportSize(QSize(1024, 768));
}

void Capture::loadFinished()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Capture::capture);
    timer->start(5000);
}

void Capture::capture()
{
    QWebFrame *mainFrame = page.mainFrame();

    QImage image(mainFrame->contentsSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    mainFrame->render(&painter);

    painter.end();

    image.save(fileName);

    QApplication::exit();
}
