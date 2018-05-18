#include "mainwindow.hpp"

MainWindow::MainWindow(int width, int height, QString title, QWidget *parent) :
    QMainWindow(parent), mainWidget{new QWidget}, hlayout{new QHBoxLayout}, server{nullptr}, logs{nullptr}, world{nullptr}
{
    qDebug() << "Création fenêtre principale ...";

    this->setWindowTitle(title);
    this->setMinimumHeight(height);
    this->setMinimumWidth(width);

    console = new QTextEdit;
    hlayout->addWidget(console);

    startServer = new QPushButton("START SERVER");
    hlayout->addWidget(startServer);

    mainWidget->setLayout(hlayout);
    this->setCentralWidget(mainWidget);

    timer = new QTimer(this);

    connect(startServer, SIGNAL(clicked()), this, SLOT(initSimulation()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::startSimulation(){
    logs = std::make_shared<SC_Register>("log-" + QDate::currentDate().toString().toStdString() + ".txt");
    world = std::make_shared<SC_Environnement>(30, 15, logs);
}

void MainWindow::initSimulation(){
    server = new QT_GenericServer;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(refreshDelay);
}

void MainWindow::update(){
    auto tmp = server->receive();

    for(auto &i : tmp){
        qDebug() << QString::fromStdString(i);
        auto cmd = cmdFormat::parseCommand(i);

        if (!cmd.command.compare("simulation")) {
            if (cmd.args.size() < 1) {
                server->send(QString::fromStdString(cmd.id), cmd.id + "@simulation:2 error no parameters");
            } else if(!cmd.args[0].compare("start")){

            }
        }
    }

    server->broadcast(logs->getLine());
}
