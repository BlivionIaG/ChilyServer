#include "QT_GenericServer.h"

QT_GenericServer::QT_GenericServer(const quint16 port, QObject *parent)
    : QObject(parent), alive{true} {
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start on port " << port << "...";
    } else {
        qDebug() << "Server started on port " << port << "!";
    }
}

QT_GenericServer::~QT_GenericServer() {
    qDebug() << "Closing server ...";
    server->close();
}

void QT_GenericServer::newConnection() {
    QTcpSocket *socket = server->nextPendingConnection();

    QString id = addClient(socket);

    connect(socket, SIGNAL(connected()), this, SLOT(clientConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(clientReceive()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void QT_GenericServer::clientConnected() {
    auto client = find(qobject_cast<QTcpSocket *>(sender()));

    qDebug() << client.key() << " is connected !";
}

void QT_GenericServer::clientReceive() {
    auto client = find(qobject_cast<QTcpSocket *>(sender()));

    auto tmpBuffer = client->clientSocket->readAll();

    if (tmpBuffer.size() <= 0) {
        qDebug() << "Error: " << client.key() << " has been disconnected !";
    } else if(!action(client.key(), tmpBuffer.toStdString())){
        buffer.append(tmpBuffer.toStdString());
    }
}

void QT_GenericServer::clientDisconnected() {
    auto client = find(qobject_cast<QTcpSocket *>(sender()));

    client->clientSocket->close();

    qDebug() << client.key() << " is disconnected !";

    clients.erase(client);
}

QString QT_GenericServer::addClient(QTcpSocket *socket) {
    QString id = QString::number(clients.size());
    QT_ClientData tmp = {alphaNumericGeneration(keyLength), socket};

    clients.insert(id, tmp);

    send(id,
         serverId + "@auth:2 " + id.toStdString().c_str() + " " + tmp.clientKey);

    return id;
}

void QT_GenericServer::broadcast(std::string message)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        send(it.key(), message);
    }
}

bool QT_GenericServer::send(QString id, std::string message) {
    if (message.length() <= 0) {
        qDebug() << "No message to send !";
        return false;
    }

    auto tmp = clients[id];
    if (tmp.clientKey.length() <= 0 && tmp.clientSocket == nullptr) {
        qDebug() << "Client " << id << " not found !";
        return false;
    }

    tmp.clientSocket->write(message.c_str());
    tmp.clientSocket->flush();

    return tmp.clientSocket->waitForBytesWritten(writeWaitTime);
}

std::vector<std::string> QT_GenericServer::receive() {
    std::vector<std::string> output;

    for (const auto &it : buffer) {
        output.push_back(it);
    }
    buffer.clear();

    return output;
}

bool QT_GenericServer::action(QString id, std::string msg) {
    auto cmd = cmdFormat::parseCommand(msg);

    if (!cmd.command.compare("shutdown")) {
        alive = false;
    } else if (!cmd.command.compare("register")) {
        if (cmd.args.size() < 3) {
            send(id, id.toStdString() + "@register:2 error wrong command");
        } else if (clients[id].clientKey.compare(cmd.args[0])) {
            send(id, id.toStdString() + "@register:2 error wrong key");
        } else {
            reregister(id, QString::fromStdString(cmd.args[1]), cmd.args[2]);
        }
    } else if (!cmd.command.compare("quit")) {
        auto dead = find(id.toStdString());

        dead->clientSocket->close();

        qDebug() << dead.key() << " is disconnected !";

        clients.erase(dead);
    } else {
        return false;
    }

    return true;
}

void QT_GenericServer::reregister(QString oldId, QString id, std::string key) {
    QT_ClientData tmp = {key, clients[oldId].clientSocket};
    clients.insert(id, tmp);

    clients.erase(clients.find(oldId));
}

QMap<QString, QT_ClientData>::iterator QT_GenericServer::find(std::string id) {
    return std::find_if(clients.begin(), clients.end(),
                        [id](QT_ClientData a) { return a.clientKey == id; });
}

QMap<QString, QT_ClientData>::iterator QT_GenericServer::find(QTcpSocket *socket) {
    return std::find_if(
                clients.begin(), clients.end(),
                [socket](QT_ClientData a) { return a.clientSocket == socket; });
}

std::string QT_GenericServer::alphaNumericGeneration(std::string::size_type length) {
    std::string charset = "0123456789"
                          "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::default_random_engine generator{std::random_device{}()};
    std::uniform_int_distribution<std::string::size_type> distribution(
                0, charset.length() - 2);

    std::string out;
    out.reserve(length);

    while (length--) {
        out += charset[distribution(generator)];
    }

    return out;
}
