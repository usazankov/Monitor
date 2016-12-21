#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "controllerarinc.h"
#include "arincmodelinterface.h"
#include "arincreader.h"
#include "arincboardpci429linux.h"
#include "formadddevice.h"
#include "formconfparamsdevice.h"
#include <iostream>
#include "device.h"
#include <QThread>
namespace Ui {
class MainController;
const QString EMPTY_CHANNEL="Нет устройств";
}
using namespace std;
class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(MainView *view, QObject *parent = 0);
    ~MainController();
private:
    MainView *view;
    QMap<int, ArincBoardInterface*> pciBoards;
    QMap<int, Device*> devices;
    QMap<int, QThread*> threads;
    FormConfParamsDevice *formConfDev;
    int countDevices;
    int countBoards;
    void connectActionsToSlots();
    int generateIndex();
    bool ThreadsisRunning();
    void checkActions();
public slots:
    void addDevice();
    void delDevice(int index);
    void confParamsDevice();
    void startDevice();
    void stopDevice();
};

#endif // MAINCONTROLLER_H
