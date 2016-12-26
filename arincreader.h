#ifndef ARINCREADER_H
#define ARINCREADER_H

#include "readingbuffer.h"
#include "parametr_impl.h"
#include "arincmodelinterface.h"
#include <QVector>
#include <QThread>
#include <QMap>
#include <QTimer>
#include <QDateTime>
#include <QMutex>
class ArincReader:public QObject, public ArincModelInterface
{
    Q_OBJECT
public:
    ArincReader(ReadingBuffer<unsigned int*> *arinc,QObject *obj=0);
    void lockMutex();
    void unlockMutex();
    ~ArincReader();
private:
    ReadingBuffer<unsigned int*> *arinc;
    QMap<int, ArincParametr*> arinc_map;
    QMap<int, ArincParametr*>::iterator iter;
    QVector<ArincParametrObserver*> observers;
    QMutex	mutex;
    int size;
    bool running;
    double time_step_to_arinc_map;
    void updateArincMap();
    void setWordsToZero();
    void deleteUnregisteredWords();
    // ArincModelInterface interface
    void stopArinc();
    void startArinc(int time_milliseconds);
    void setTypeParametr(int adress, Parametr::TypeParametr type);
    ArincParametr *getParametr(int adress);
    Parametr::TypeParametr TypeParametr(int adress);
    void addArincParametr(ArincParametr *arincword);
    void registerObserver(ArincParametrObserver *o);
    void removeObserver(ArincParametrObserver *o);
    void notifyObservers();
    static int count_model;
    QTimer *timer;
private slots:
    void update();
signals:
    void stopTimer();
    void start_Timer(int);
    // ArincModelInterface interface
public:
    bool hasArincParametr(int adress);

    // ArincModelInterface interface
public:
    bool isRunningArinc();

    // ArincModelInterface interface
public:
    void clearParametrs();

};

#endif // ARINCREADER_H
