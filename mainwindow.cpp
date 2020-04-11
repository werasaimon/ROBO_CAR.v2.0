#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create a QUDP socket
    m_socket      = new QUdpSocket(this);
    timer         = new QTimer(this);

    connect(ui->pushButton_OnOFF , SIGNAL(clicked()) , this , SLOT(onStartTime()) );
    connect(timer , SIGNAL(timeout()) , this , SLOT(Updatee()) );

    connect(ui->horizontalSliderX, SIGNAL(valueChanged(int)), this, SLOT(SliderSpeedX(int)));
    connect(ui->horizontalSliderY, SIGNAL(valueChanged(int)), this, SLOT(SliderSpeedY(int)));

    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(DialCofficient(int)));

    CofficientTurn = 1;

    coff = 1;

    // Инициализация SDL для использования джойстика
     SDL_Init(SDL_INIT_JOYSTICK);
     // Включаем
     SDL_JoystickEventState(SDL_ENABLE);
     // Открываем ;)
     joy = SDL_JoystickOpen(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onStartTime()
{
    // Запускаем таймер
    if(!timer->isActive())
    {
        timer->start(50);

        ui->pushButton_OnOFF->setText("STOP");
    }
    else
    {
        data_trransmission.speedX=0;
        data_trransmission.speedY=0;
        Updatee();

        timer->stop();

        ui->pushButton_OnOFF->setText("START");


    }

}

void MainWindow::Updatee()
{

    data_trransmission.enLED = false;

    if(ui->checkGamepad->isChecked())
    {
      // Обробатываем событие джойстика
      SDL_PollEvent(&event);

     // Получаем значения, соответствующие смещению  аналгово джойстика
      yAxis = SDL_JoystickGetAxis(joy, 1);
      xAxis = SDL_JoystickGetAxis(joy, 0);

      qDebug() << "xAxis " << xAxis << "  yAxis " << yAxis;

      ui->horizontalSliderX->setValue(xAxis);
      ui->horizontalSliderY->setValue(yAxis);

      if(SDL_JoystickGetButton(joy,1))
      {
          qDebug() << "LED";
          data_trransmission.enLED = true;
      }
    }

     //---------------------------------------------------------------//

     int mSpeed = yAxis / 32;
     int mTurn  = xAxis / 32;
    //float mCofficientTurn = 1.f;///CofficientTurn;

      //qDebug() << "turn " << mTurn / coff;

     data_trransmission.speedX = int(-mSpeed - mTurn / coff);
     data_trransmission.speedY = int(-mSpeed + mTurn / coff);


     //---------------------------------------------------------------//

     // отыслаем данные на ROBO_CAR
     QString ipAddresStr = ui->lineEdit->text();
     m_socket->writeDatagram( (char*)&data_trransmission , sizeof(dataTransmission) , QHostAddress( ipAddresStr ) , 8888);


    char buff[255]="no packet .... \n";
    int nsize = m_socket->readDatagram( buff , 255 );
    buff[nsize]=0;


    ui->plainTextEdit->setPlainText(buff);
    qDebug() << nsize << buff;
}


void MainWindow::SliderSpeedX(int value)
{
    ///qDebug() << value;
    xAxis = value;
}


void MainWindow::SliderSpeedY(int value)
{
    ///qDebug() << value;
    yAxis = value;
}

void MainWindow::DialCofficient(int value)
{
    qDebug() << value;
    coff = value;
}



