#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    m_server = new Server(this);
    connect(m_server, SIGNAL(receivedGetRequest(QTcpSocket*)),
            this, SLOT(hasReceivedGetRequest(QTcpSocket*)));
    connect(m_server, SIGNAL(receivedPostRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)),
            this, SLOT(hasReceivedPostRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)));
    connect(m_server, SIGNAL(receivedPutRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)),
            this, SLOT(hasReceivedPutRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)));
    connect(m_server, SIGNAL(receivedDeleteRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)),
            this, SLOT(hasReceivedDeleteRequest(QTcpSocket*,QMap<QByteArray,QByteArray>)));

    m_universities.append("Universidade Federal de Alagoas");
    m_universities.append("Universidade Federal da Bahia");
    m_universities.append("Universidade Federal de Sergipe");
    m_universities.append("Universidade Federal de Minas Gerais");
    m_universities.append("Universidade Federal de Pernambuco");
    m_universities.append("Universidade Federal do Rio de Janeiro");
    m_universities.append("Pontifícia Universidade Católica do Rio de Janeiro");
}

void NetworkManager::hasReceivedGetRequest(QTcpSocket *socket)
{
    Client *client = new Client(this);
    if(client->connectToSocket(socket)) {
        qDebug() << "MESSAGE HAS BEEN SENT: " << client->writeData(toJSON());
    } else {
        qDebug() << "ERR01.0 CANNOT CONNECT : " << socket->state();
    }
    client->deleteLater();
    socket->disconnectFromHost();
}

void NetworkManager::hasReceivedPostRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap)
{
    Client *client = new Client(this);
    if(client->connectToSocket(socket)) {
        bool check = false;
        foreach (QByteArray key, parametersMap.keys()) {
            if(key == "university") {
                m_universities.append(parametersMap.value(key));
                check = true;
            }
        }
        if(check)
            qDebug() << "MESSAGE HAS BEEN SENT: " << client->writeData("University added with sucess!");
        else
            qDebug() << "MESSAGE HAS BEEN SENT: " << client->writeData("University wasn't added!");

    } else {
        qDebug() << "ERR02.0 CANNOT CONNECT : " << socket->state();
    }
    client->deleteLater();
    socket->disconnectFromHost();
}

void NetworkManager::hasReceivedPutRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap)
{
    qDebug() << parametersMap;
    Client *client = new Client(this);
    if(client->connectToSocket(socket)) {
        foreach (QByteArray key, parametersMap.keys()) {
            bool check = false;
            if(m_universities.contains(key)) {
                m_universities.removeOne(key);
                m_universities.append(parametersMap.value(key));
                check = true;
            }
            if(check)
                qDebug() << "MESSAGE HAS BEEN SENT: " << client->writeData("University was updated with sucess!\n");
            else
                qDebug() << "MESSAGE HAS BEEN SENT: " << client->writeData("University wasn't updated!\n");
        }

    } else {
        qDebug() << "ERR03.0 CANNOT CONNECT : " << socket->state();
    }
    client->deleteLater();
    socket->disconnectFromHost();
}

void NetworkManager::hasReceivedDeleteRequest(QTcpSocket *socket, QMap<QByteArray, QByteArray> parametersMap)
{
    Client *client = new Client(this);
    if(client->connectToSocket(socket)) {
        bool check = false;
        foreach (QByteArray key, parametersMap.keys()) {
            if(key == "university") {
                check = m_universities.removeOne(parametersMap.value(key));
            }
        }
        if(check)
            qDebug() << "SUCC4.1 MESSAGE HAS BEEN SENT: " << client->writeData("University was deleted with sucess!");
        else
            qDebug() << "ERR04.1 MESSAGE HAS BEEN SENT: " << client->writeData("University wasn't deleted!");

    } else {
        qDebug() << "ERR04.0 CANNOT CONNECT : " << socket->state();
    }
    client->deleteLater();
    socket->disconnectFromHost();
}

QByteArray NetworkManager::toJSON()
{
    QJsonObject mainObject;
    QJsonArray universitiesArray;
    foreach (QByteArray university, m_universities) {
        universitiesArray.append(QString(university));
    }
    mainObject.insert("universities", universitiesArray);

    QJsonDocument jsonDocument(mainObject);
    return jsonDocument.toJson();
}
