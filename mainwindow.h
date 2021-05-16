#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QVector>
#include <QHash>
#include <QString>
#include <random>
#include <QPushButton>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer();
    QTime time;
    int parejasRestantes;
    QMessageBox msgBox;
    QVector<QString> tarjetas{"tarjeta01", "tarjeta02", "tarjeta03", "tarjeta04",
                             "tarjeta05", "tarjeta06", "tarjeta07", "tarjeta08",
                             "tarjeta09", "tarjeta10", "tarjeta11", "tarjeta12"};
    QHash<QString, QString> reparto;
    int puntaje;
    bool jugadaIniciada;
    QPushButton* tarjetaAnterior;
    QPushButton* tarjetaActual;

private slots:
    void actualizarEstado();
    void actualizarCronometro();
    void definirResultadoFinal();
    void inicializarJuego();
    void tarjetaDescubierta();
    void mezclar(QVector<QString> &tarjetas);
    void repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto);
    void MostrarImagen();
    void definirResultadoParcial();
    void reiniciarTarjetas();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
