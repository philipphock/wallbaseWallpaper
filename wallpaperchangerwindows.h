#ifndef WALLPAPERCHANGERWINDOWS_H
#define WALLPAPERCHANGERWINDOWS_H
#include <QtGui/QApplication>
#include <QtWebKit/QWebView>
#include <QtCore/QUrl>
#include "uriloader.h"
#include <wchar.h>
#include <wininet.h>
#include <shlobj.h>



class WallpaperChangerWindows : public QObject
{
    Q_OBJECT
private:
    UriLoader* loader;

public:
    WallpaperChangerWindows(UriLoader* loader);

public slots:
    void setWallpaper();
};


#endif // WALLPAPERCHANGERWINDOWS_H
