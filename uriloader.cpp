#include <QtGui/QApplication>
#include "uriloader.h"
#include <QtWebKit>
#include <iostream>
#include <QRegExp>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>


UriLoader::UriLoader(const QUrl& url){

    pageLoader = new QWebView();
    imageLoader = new QWebView();
    netwManager = new QNetworkAccessManager();



    connect(pageLoader, SIGNAL(loadFinished(bool)),this, SLOT(pageLoaded(bool)));
    connect(imageLoader, SIGNAL(loadFinished(bool)),this, SLOT(imagePageLoaded(bool)));
    connect(netwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(imageFileLoaded(QNetworkReply*)));

    pageLoader->load(url);

}


void UriLoader::pageLoaded(bool ok){
    const QString selector=QString("html body div#delwrap a.thdraggable");

    QWebElementCollection pictures = pageLoader->page()->currentFrame()->findAllElements(selector);


    //qDebug()<<"page loaded" ;
    std::cout << "page loaded" << std::endl;
    if (pictures.count() > 0){
        //get first image url
        const QString imageUrl = pictures[0].attribute("href");
        //qDebug()<<"image url found";
        std::cout << "image url found" << std::endl;
        //load image
        imageLoader->load(QUrl(imageUrl));
        //qDebug()<<"loading image " << imageUrl;
        std::cout << "loading image " << (imageUrl.toStdString().c_str()) << std::endl ;
    }else{
        //qDebug()<<"error loading uri";
        std::cerr << "error loading uri"  << std::endl;
        pageLoader->close();
        emit imageDownloaded();
        QApplication::exit(1);
    }

}

void UriLoader::imagePageLoaded(bool ok){
    //qDebug()<<"image-page loaded";
    std::cout <<"image-page loaded" << std::endl;
    QWebElementCollection imgs = imageLoader->page()->currentFrame()->findAllElements("html body div#bigwall img");
    if (imgs.count() > 0){
        QString imageUrl = imgs[0].attribute("src");
        //qDebug()<<"image-tag found: "<<imageUrl ;
        std::cout << "image-tag found: " <<imageUrl.toStdString()  << std::endl;
        imgRequest = new QNetworkRequest(imageUrl);
        netwManager->get(*imgRequest);
    }else{
        qDebug("error: no image-tags found on image-page");
        std::cerr << "error: no image-tags found on image-page"  << std::endl;
        QApplication::exit(1);
    }






}

void UriLoader::imageFileLoaded(QNetworkReply* reply){
    //qDebug("image file downloaded");
    std::cout << "image file downloaded";
    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
    QString imgFileEnding = "unknown";
    if (contentType.type() == QVariant::String){
        if(contentType.toString() == "image/jpeg"){
            imgFileEnding = "jpg";
        }else if(contentType.toString() == "image/png"){
            imgFileEnding = "png";
        }else{
            //qDebug("error: imagefile-type unknown");
            std::cerr << "error: imagefile-type unknown";
            QApplication::exit(1);
        }

    }else{
        //qDebug("error: no imagefile downloaded");
        std::cerr << "error: no imagefile downloaded";
        QApplication::exit(1);
    }

    QPixmap converter;
    converter.loadFromData(reply->readAll(),"JPG");
    converter.save("random.bmp","BMP");
    /*
    QFile imgFile();
    imgFile.open(QIODevice::WriteOnly);

    imgFile.write(reply->readAll());
    */
    emit imageDownloaded();
}

void UriLoader::cleanup_connections(){
    imageLoader->close();
    pageLoader->close();
}

UriLoader::~UriLoader(){
    //delete imageLoader;
    //delete pageLoader;
    //delete netwManager;
}
