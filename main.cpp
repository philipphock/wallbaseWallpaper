#include <QtGui/QApplication>
#include <iostream>
#include <QtWebKit/QWebView>
#include "uriloader.h"
#include "wallpaperchangerwindows.h"
int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QUrl url("http://www.wallbase.cc/random/");

    UriLoader uriLoader(url);

    WallpaperChangerWindows wpc(&uriLoader);


    return app.exec();
}
