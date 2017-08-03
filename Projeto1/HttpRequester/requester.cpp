#include "requester.h"

Requester::Requester(QObject *parent) : QObject(parent)
{
    //GET EXAMPLE
//        get("192.168.1.199", "35353");

    //POST EXAMPLE
//        QMap<QByteArray, QByteArray> postBody;
//        postBody.insert("payload", "university=Universidade Federal de São Paulo");
//        post("192.168.1.199", "35353", postBody);


    //PUT EXAMPLE
//        QMap<QByteArray, QByteArray> putBody;
//        putBody.insert("payload", "Universidade Federal de Alagoas=Universidade Federal de São Paulo");
//        put("192.168.1.199", "35353", putBody);

//    DELETE EXAMPLE
//        deleteResource("192.168.1.199", "35353", "Universidade Federal de Alagoas");
}

void Requester::get(QByteArray adress, QByteArray port)
{
    if(adress.contains("http://")) adress.replace("http://","");
    if(adress.contains("https://")) adress.replace("https://","");

    QNetworkRequest _request(QUrl("http://localhost:8081/service.php"));
    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    _request.setRawHeader("fulladdress", "http://" + adress + ":" + port);

    QNetworkAccessManager *nm = new QNetworkAccessManager(this);

    connect(nm, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyArrived(QNetworkReply*)));

    nm->get(_request);
}

void Requester::post(QByteArray adress, QByteArray port, QMap<QByteArray, QByteArray> bodyArguments)
{
    QUrlQuery params;
    params.addQueryItem("_data", toJson(bodyArguments));

    QByteArray _data;
    _data.append(params.query());
    _data.remove(0,1);

    if(adress.contains("http://")) adress.replace("http://","");
    if(adress.contains("https://")) adress.replace("https://","");

    QNetworkRequest _request(QUrl("http://localhost:8081/service.php"));
    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    _request.setRawHeader("fulladdress", "http://" + adress + ":" + port);

    QNetworkAccessManager *nm = new QNetworkAccessManager(this);

    connect(nm, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyArrived(QNetworkReply*)));

    nm->post(_request, _data);
}

void Requester::put(QByteArray adress, QByteArray port, QMap<QByteArray, QByteArray> bodyArguments)
{
    QUrlQuery params;
    params.addQueryItem("_data", toJson(bodyArguments));

    QByteArray _data;
    _data.append(params.query());
    _data.remove(0,1);

    if(adress.contains("http://")) adress.replace("http://","");
    if(adress.contains("https://")) adress.replace("https://","");

    QNetworkRequest _request(QUrl("http://localhost:8081/service.php"));
    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    _request.setRawHeader("fulladdress", "http://" + adress + ":" + port);

    QNetworkAccessManager *nm = new QNetworkAccessManager(this);

    connect(nm, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyArrived(QNetworkReply*)));

    nm->put(_request, _data);
}

void Requester::deleteResource(QByteArray adress, QByteArray port,QByteArray args)
{
    if(adress.contains("http://")) adress.replace("http://","");
    if(adress.contains("https://")) adress.replace("https://","");

    QNetworkRequest _request(QUrl("http://localhost:8081/service.php"));
    _request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    _request.setRawHeader("fulladdress", "http://" + adress + ":" + port);
    _request.setRawHeader("university", args);

    QNetworkAccessManager *nm = new QNetworkAccessManager(this);

    connect(nm, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyArrived(QNetworkReply*)));
    nm->deleteResource(_request);
}

void Requester::replyArrived(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
    sender()->deleteLater();
}

QByteArray Requester::toJson(QMap<QByteArray,QByteArray> map)
{
    QJsonObject mainObject;
    foreach (QByteArray key, map.keys()) {
        mainObject.insert(key, QString(map.value(key)));
    }
    QJsonDocument doc(mainObject);
    return doc.toJson();
}
