#ifndef REQUESTER_H
#define REQUESTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrlQuery>
#include <QObject>
#include <QDebug>

class Requester : public QObject
{
    Q_OBJECT
public:
    explicit Requester(QObject *parent = nullptr);
    void get(QByteArray adress, QByteArray port);
    void post(QByteArray adress, QByteArray port, QMap<QByteArray, QByteArray> bodyArguments);
    void put(QByteArray adress, QByteArray port, QMap<QByteArray, QByteArray> bodyArguments);
    void deleteResource(QByteArray adress, QByteArray port, QByteArray args);
private slots:
    void replyArrived(QNetworkReply *reply);
private:
    QByteArray toJson(QMap<QByteArray, QByteArray> map);
};

#endif // REQUESTER_H
