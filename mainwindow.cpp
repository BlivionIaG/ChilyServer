#include "mainwindow.hpp"

MainWindow::MainWindow(int width, int height, QString title, QWidget *parent) :
    QMainWindow(parent), mainWidget{new QWidget}, hlayout{new QHBoxLayout}, server{nullptr}, logs{nullptr}, world{nullptr}
{
    this->setWindowTitle(title);
    this->setMinimumHeight(height);
    this->setMinimumWidth(width);

    console = new QTextEdit; // "Console" de reception et d'info basique du serveur
    hlayout->addWidget(console);

    startServer = new QPushButton("START SERVER"); // bouton pour démarrer le serveur
    hlayout->addWidget(startServer);

    mainWidget->setLayout(hlayout); //Ajout du layout au widget principal
    this->setCentralWidget(mainWidget);

    timer = new QTimer(this); //Déclaration du timer

    pause = false; //Pas de pause par défaut

    println("Création fenêtre principale ...");

    connect(startServer, SIGNAL(clicked()), this, SLOT(initSimulation()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::startSimulation(int width, int height, int lions, int gazelles){
    println("Création du registre ...");
    logs = std::make_shared<SC_Register>("log-" + QDate::currentDate().toString().toStdString() + ".txt");
    println("Création de l'environnement ...");
    world = std::make_shared<SC_Environnement>(width, height, logs);
    println("Mise en place de la populasse ...");
    world->populate(lions, gazelles);
}

void MainWindow::initSimulation(){
    server = new QT_GenericServer;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(refreshDelay);
}

void MainWindow::update(){
    auto tmp = server->receive();

    for(auto &i : tmp){
        println(QString::fromStdString(i));
        auto cmd = cmdFormat::parseCommand(i);

        if (!cmd.command.compare("simulation")) {
            if (cmd.args.size() < 1) {
                server->send(QString::fromStdString(cmd.id), cmd.id + "@simulation:2 error no parameters");
            } else if(!cmd.args[0].compare("start")){
                switch(cmd.args.size()){
                case 0:
                    server->send(QString::fromStdString(cmd.id), cmd.id + "@simulation:2 error no parameters");
                    break;
                case 2:
                    startSimulation(std::atoi(cmd.args[1].c_str()));
                    break;
                case 3:
                    startSimulation(std::atoi(cmd.args[1].c_str()), std::atoi(cmd.args[2].c_str()));
                    break;
                case 4:
                    startSimulation(std::atoi(cmd.args[1].c_str()), std::atoi(cmd.args[2].c_str()), std::atoi(cmd.args[3].c_str()));
                    break;
                case 5:
                    startSimulation(std::atoi(cmd.args[1].c_str()), std::atoi(cmd.args[2].c_str()), std::atoi(cmd.args[3].c_str()), std::atoi(cmd.args[4].c_str()));
                    break;
                default:
                    startSimulation();
                    break;
                }
            }
        }else if(!cmd.command.compare("pause")){
            if(cmd.args.size() < 1){
                pause = !pause;
            } else if(!cmd.args[0].compare("on")) {
                pause = true;
            }else if(!cmd.args[0].compare("off")){
                pause = false;
            }
        }else if(!cmd.command.compare("delay")){
            if(cmd.args.size() < 1){
                server->send(QString::fromStdString(cmd.id), cmd.id + "@delay:2 error no parameters");
            }else{
                timer->setInterval(std::atoi(cmd.args[0].c_str()));
            }
        }
    }

    if(!pause && logs != nullptr){
        if(world != nullptr) world->moveAnimals();

        auto btmp = logs->getLine();
        if(btmp.size() > 0) {
            server->broadcast(btmp);
            //println(QString::fromStdString(btmp));
        }
    }
}

void MainWindow::println(const QString line){
    qDebug() << line;
    console->insertPlainText(line + "\n");
}
