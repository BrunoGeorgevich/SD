#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

//Json Includes
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QObject>

#include "server.h"
#include "client.h"

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
private slots:
    void hasReceivedGetRequest(QTcpSocket *socket);
    void hasReceivedPostRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap);
    void hasReceivedPutRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap);
    void hasReceivedDeleteRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap);
private:
    QByteArray toJSON();

    Server *m_server;
    QList<QByteArray> m_universities;
};

#endif // NETWORKMANAGER_H
