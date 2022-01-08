#include <wiringPi.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <unistd.h>
#define Trig 0
#define Echo 3
#define DO 24
#define LENGTH 20
#define d 10
#define n 5
using namespace std;
void pinSetup(void)
{
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
    pinMode(DO, INPUT);
    digitalWrite(Trig, LOW);
}
int Lightup(double speed，int x[])
{
    if (speed <= )
    {
        digitalWrite(x[0], HIGH); 
        digitalWrite(x[1], LOW);
        digitalWrite(x[2], LOW);
    }
    else if (speed >= && speed <= )
    {
        digitalWrite(x[1], HIGH);
        digitalWrite(x[0], LOW);
        digitalWrite(x[2], LOW);
    }
    else
    {
        digitalWrite(x[2], HIGH);
        digitalWrite(x[1], LOW);
        digitalWrite(x[0], LOW);
    }
}
void Warning(void)
{
    if (!digitalRead(DO))
        digitalWrite(x[3], HIGH);
}
double getDistance(void)
{
    struct timeval t1;
    struct timeval t2;
    digitalWrite(Trig, LOW);
    delay(10);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    while (!(digitalRead(Echo) == 1))
        gettimeofday(&t1, NULL);
    while (!(digitalRead(Echo) == 0))
        gettimeofday(&t2, NULL);
    double ft1, ft2;
    ft1 = t1.tv_sec * 1000000 + t1.tv_usec;
    ft2 = t2.tv_sec * 1000000 + t2.tv_usec;
    double dis = (ft2 - ft1) / 1000000 * 34000 / 2;
    return dis;
}
int main()
{
    int x[n] = {0};
    if (wiringPiSetup() == -1)
    {
        cout << "Setup Failed！" << endl;
        return -1;
    }
    else
    {
        pinSetup();  
        cout << "Please input the GPIO number of light:(input -1 to end)" << endl;
        for (i = 0; i < n; i++)
        {
            cin >> x[i];
            if (x[i] == -1)
                break;
            else
                pinMode(x[i], OUTPUT);
        }
    }
    //初始化
    Warning();
    double dis1, cdis;
    struct timeval startTime, finalTime, dTime;
    cdis = getDistance();//第一次距离作为基准
    while (1)
    {
        dis1 = getDistance();
        if (cdis - dis1 > d)
        {
            gettimeofday(&startTime, NULL);
        }
        if (dis1 - cdis > d)
        {
            gettimeofday(&finalTime, NULL);
            dTime.tv_sec = finalTime.tv_sec - startTime.tv_sec;
            dTime.tv_usec = finalTime.tv_usec - startTime.tv_usec;
        }
        long long MicrodTime = dTime.tv_sec * 1000000 + dTime.tv_usec;
        //计算时间差（实验中距离取固定值）
        double SdTime = MicrodTime / 1000000.0;
        double speed = LENGTH / SdTime;
        Lightup(speed, x);
    }
}