#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QDate>

#include <memory>

#include "QT_GenericServer.h"
#include "SC_Environnement.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int width = 800, int height = 600, QString title = "Chily Con Carne Server", QWidget *parent = 0);
    ~MainWindow();

    void startSimulation();
public slots:
    void update();
    void initSimulation();
private:
    QWidget *mainWidget;
    QHBoxLayout *hlayout;

    /* Timer */
    QTimer *timer;

    /* Console du Serveur */
    QTextEdit *console;
    /* Bouton de démarrage du serveur */
    QPushButton *startServer;

    /* Serveur */
    QT_GenericServer *server;

    /* Logs */
    std::shared_ptr<SC_Register> logs;
    std::shared_ptr<SC_Environnement> world;

    const int refreshDelay = 20;
};

#endif // MAINWINDOW_HPP
