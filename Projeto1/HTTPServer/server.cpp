#include "server.h"

static inline qint32 ArrayToInt(QByteArray source);

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    qDebug() << "Listening:" << server->listen(QHostAddress::Any, 35353);
}

void Server::newConnection()
{
    while (server->hasPendingConnections())
    {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);

        qDebug() << "{\n  Connected :"
                 << "\n\tIP  :"   << socket->peerAddress()
                 << "\n\tPORT:" << socket->peerPort()
                 << "\n}";
    }
}

void Server::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void Server::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray httpHeaders = socket->readAll();

    QByteArray requestType = httpHeaders.split('\n').at(0);
    if(requestType.contains("POST")) {
        qDebug() << "POST!!";
        emit receivedPostRequest(socket, extractParameters(httpHeaders));
    } else if(requestType.contains("GET")) {
        qDebug() << "GET!!";
        emit receivedGetRequest(socket);
    } else if(requestType.contains("PUT")) {
        qDebug() << "PUT!!";
        emit receivedPutRequest(socket, extractParameters(httpHeaders));
    } else if(requestType.contains("DELETE")) {
        qDebug() << "DELETE!!";
        emit receivedDeleteRequest(socket, extractParameters(httpHeaders));
    } else {
        qDebug() << "OTHERS!!";
        qDebug() << httpHeaders;
    }
}

QMap<QByteArray, QByteArray> Server::extractParameters(QByteArray &httpHeader)
{

    QByteArray parameters = QUrl::fromPercentEncoding(httpHeader).toLatin1().split('\n').last();
    QMap<QByteArray, QByteArray> parametersMap;

    foreach (QByteArray str, parameters.split('&')) {
        parametersMap.insertMulti(str.split('=').at(0), str.split('=').at(1));
    }

    return parametersMap;
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
