#include <QtWebKitWidgets>

class Capture : public QObject
{
    Q_OBJECT

public:
    Capture();
    void load(const QUrl &url, const QString &outputFileName);
    void loadFinished();

private:
    QWebPage page;
    QString fileName;

    void capture();
};
