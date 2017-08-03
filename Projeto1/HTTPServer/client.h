#include <QtCore>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
public slots:
    bool connectToSocket(QTcpSocket *socket);
    bool writeData(QByteArray data);

private:
    QTcpSocket *m_socket;
};
