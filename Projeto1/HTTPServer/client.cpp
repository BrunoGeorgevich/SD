#include "client.h"

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject *parent) : QObject(parent)
{ }

bool Client::connectToSocket(QTcpSocket *socket)
{
    m_socket = socket;
    return socket->isWritable();
}

bool Client::writeData(QByteArray data)
{
    if(m_socket->state() == QAbstractSocket::ConnectedState)
    {
        m_socket->write(IntToArray(data.size())); //write size of data
        m_socket->write(data); //write the data itself
        return m_socket->waitForBytesWritten();
    }
    else
        return false;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
