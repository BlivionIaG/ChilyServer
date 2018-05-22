#ifndef QT_GENERICSERVER_H
#define QT_GENERICSERVER_H

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include <random>
#include <string>
#include <utility>
#include <vector>

#include "cmdFormat.hpp"

struct QT_ClientData {
    std::string clientKey;
    QTcpSocket *clientSocket;
};

class QT_GenericServer : public QObject {
    Q_OBJECT
public:
    explicit QT_GenericServer(const quint16 port = 42080, QObject *parent = nullptr);
    ~QT_GenericServer();

    bool isAlive() const { return alive; }
    void toggleAlive() { alive = !alive; }
    void setAlive(bool parm) { alive = parm; }

    QString addClient(QTcpSocket *socket);
    void broadcast(std::string message);
    bool send(QString id, std::string message);
    std::vector<std::string> receive();

    bool action(QString id, std::string message);
    void reregister(QString oldId, QString id, std::string key);

    QMap<QString, QT_ClientData>::iterator find(std::string id);
    QMap<QString, QT_ClientData>::iterator find(QTcpSocket *socket);

    /* Alpha-numeric generator */
    std::string alphaNumericGeneration(std::string::size_type length);
signals:

public slots:
    void newConnection();
    void clientConnected();
    void clientReceive();
    void clientDisconnected();

private:
    bool alive;
    QTcpServer *server;
    QVector<std::string> buffer;
    QMap<QString, QT_ClientData> clients;

    const uint keyLength = 16;
    const uint writeWaitTime = 3000;
    const std::string serverId = "SERVER";
};

#endif // QT_GENERICSERVER_H
