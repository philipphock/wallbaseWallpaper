#include "wallpaperchangerwindows.h"
#include <QProcess>
#include <iostream>
#include <QDir>
#include <QSettings>
WallpaperChangerWindows::WallpaperChangerWindows(UriLoader* loader){
    connect(loader,SIGNAL(imageDownloaded()),this,SLOT(setWallpaper()));
    this->loader=loader;
}

void WallpaperChangerWindows::setWallpaper(){
    //qDebug("now calling wallpaper change script");

    QString wpdir=QDir::currentPath().replace("/","\\")+"\\random.bmp";


    //Read currect windows background image path <from http://qtwiki.org/Set_windows_background_using_QT>
    QSettings appSettings( "HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);

    //Set new background path
    appSettings.setValue("Wallpaper", wpdir);
    QByteArray ba = wpdir.toLatin1();
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)ba.data(),	SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE); //Notification to windows renew desktop
    loader->cleanup_connections();
}









