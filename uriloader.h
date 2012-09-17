#ifndef URILOADER_H
#define URILOADER_H
#include <QtGui/QApplication>
#include <QtWebKit/QWebView>
#include <QtCore/QUrl>

class UriLoader : public QObject
{
    Q_OBJECT
public:
    UriLoader(const QUrl& url);
    virtual ~UriLoader();
private:
    QWebView* pageLoader;
    QWebView* imageLoader;
    QNetworkRequest* imgRequest;
    QNetworkAccessManager* netwManager;

public slots:
    void pageLoaded(bool ok);
    void imagePageLoaded(bool ok);
    void imageFileLoaded(QNetworkReply* reply);
    void cleanup_connections();

signals:
    void imageDownloaded(void);
};


#endif // URILOADER_H
