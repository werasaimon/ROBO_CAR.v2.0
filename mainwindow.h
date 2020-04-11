#ifndef MAINWINDOW_H
#define MAINWINDOW_H


// Подключаем SDL
#include <SDL/SDL.h>
// main определена и в SDL и в QT, поэтому #undef
#undef main


#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>
#include <QVector2D>

#include <QMouseEvent>



namespace Ui
{
  class MainWindow;
}

// Структура данных для ROBO_CAR
struct dataTransmission
{   
    int speedX = 0;
    int speedY = 0;
    bool  enLED = false;
};


QT_USE_NAMESPACE


class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();


    private slots:

        void onStartTime();
        void Updatee();


        void SliderSpeedX( int value );
        void SliderSpeedY( int value );
        void DialCofficient( int value );



    private:

        int coff;

        Ui::MainWindow *ui;

        dataTransmission data_trransmission;

        QUdpSocket *m_socket;

        QTimer *timer;

        // Переменная для нашего джойстика
        SDL_Joystick *joy;
        SDL_Event event;

        int xAxis;
        int yAxis;

        int CofficientTurn;

};

#endif // MAINWINDOW_H
