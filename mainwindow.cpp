#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarEstado()));
    connect(ui->tarjeta01, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta02, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta03, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta04, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta05, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta06, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta07, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta08, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta09, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta10, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta11, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    connect(ui->tarjeta12, SIGNAL(clicked()), this, SLOT(tarjetaDescubierta()));
    inicializarJuego();

}

void MainWindow::tarjetaDescubierta(){
    tarjetaActual = qobject_cast<QPushButton*>(sender());
    MostrarImagen();
    tarjetaActual->setEnabled(false);
    if (!jugadaIniciada){
        tarjetaAnterior = tarjetaActual;
        jugadaIniciada = true;
    }
    else{
        definirResultadoParcial();
        jugadaIniciada = false;
    }
}

void MainWindow::MostrarImagen(){
    QString nombre_tarjeta = tarjetaActual->objectName();
    QString img = reparto[nombre_tarjeta];
    tarjetaActual->setStyleSheet("#" + nombre_tarjeta + "{ background-image: url(://" + img + ") }");

}

void MainWindow::reiniciarTarjetas(){
    tarjetaAnterior->setStyleSheet("#" + tarjetaAnterior->objectName() + "{}");
    tarjetaActual->setStyleSheet("#" + tarjetaActual->objectName() + "{}");
    tarjetaActual->setEnabled(true);
    tarjetaAnterior->setEnabled(true);
    ui->frame->setEnabled(true);
}

void MainWindow::definirResultadoFinal(){
    msgBox.setWindowTitle("Juego terminado");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);

    if (parejasRestantes == 0){
        timer->stop();
        msgBox.setText("Ganaste! Puntuación final: " + QString::number(puntaje) + "\n¿Volver a jugar?");
        if (QMessageBox::Yes == msgBox.exec()){
            inicializarJuego();
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString() == "00:00:00"){
            timer->stop();
            ui->frame->setEnabled(false);
            msgBox.setText("Perdiste. \n¿Volver a jugar?");
            if (QMessageBox::Yes == msgBox.exec()){
                inicializarJuego();
            }
            else{
                QCoreApplication::quit();
            }
        }
    }
}

void MainWindow::definirResultadoParcial(){
    if (reparto[tarjetaActual->objectName()] == reparto[tarjetaAnterior->objectName()]){
        puntaje += 15;
        ui->lblPuntaje->setText(QString::number(puntaje));
        parejasRestantes--;
        definirResultadoFinal();
    }
    else{
        puntaje -= 5;
        ui->lblPuntaje->setText(QString::number(puntaje));
        ui->frame->setEnabled(false);
        QTimer::singleShot(1000, this, SLOT(reiniciarTarjetas()));
    }
}

void MainWindow::inicializarJuego(){
    jugadaIniciada = false;
    puntaje = 0;
    ui->lblPuntaje->setText(QString::number(puntaje));
    parejasRestantes = 6;
    time.setHMS(0, 1, 0);
    ui->cronometro->setText(time.toString("m:ss"));
    timer->start(1000);
    mezclar(tarjetas);
    repartir(tarjetas, reparto);
    ui->frame->setEnabled(true);
    QList<QPushButton*> botones = ui->centralwidget->findChildren<QPushButton*>();
    foreach (QPushButton* b, botones){
        b->setEnabled(true);
        b->setStyleSheet("#" + b->objectName() + "{}");
    }
}

void MainWindow::actualizarCronometro(){
    time = time.addSecs(-1);
    ui->cronometro->setText(time.toString("m:ss"));
}

void MainWindow::actualizarEstado(){
    actualizarCronometro();
    definirResultadoFinal();
}

void MainWindow::mezclar(QVector<QString> &tarjetas){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(tarjetas.begin(), tarjetas.end(), std::default_random_engine(seed));
}

void MainWindow::repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto){
    auto iterador = tarjetas.begin();

    for (int i = 1; i<=6; i++){
        QString file_name = "0" + QString::number(i) + ".png";
        reparto[(*iterador)] = file_name;
        iterador++;
        reparto[(*iterador)] = file_name;
        iterador++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

