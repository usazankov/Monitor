#ifndef ARINCMODELINTERFACE_H
#define ARINCMODELINTERFACE_H
#include "arincparametrobserver.h"
class ArincModelInterface{
public:
    virtual void startArinc(int time_milliseconds=1000)=0;
    virtual void stopArinc()=0;
    virtual void setTypeParametr(int adress, Parametr::TypeParametr type)=0;
    virtual ArincParametr* getParametr(int adress)=0;
    virtual Parametr::TypeParametr TypeParametr(int adress)=0;
    virtual int indexModel()=0;
    virtual void registerObserver(ArincParametrObserver *o)=0;
    virtual void removeObserver(ArincParametrObserver *o)=0;
    virtual void notifyObservers()=0;
    virtual ~ArincModelInterface(){}
};
#endif // ARINCMODELINTERFACE_H