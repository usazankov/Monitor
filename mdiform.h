#ifndef MDIFORM_H
#define MDIFORM_H

#include <QWidget>
#include "controllerinterface.h"
#include "arincmodelinterface.h"
#include <QAbstractTableModel>
#include <QHash>
#include <iostream>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
namespace Ui {
class MdiForm;
class ModelTable;
class QLabelHasWord;
const int COLUMNS_MAIN_TABLE=6;
const int ROWS_MAIN_TABLE=5;

const QString TABLE_NAME="Имя";
const QString TABLE_VALUE="Значение";
const QString TABLE_UNPACK="Всё слово";
const QString TABLE_DIMENSION="Ед.изм";
const QString TABLE_MS="МС";
const QString TABLE_ADRESS="Адрес";
const QString TABLE_STATE="Значение";
}
class QLabelHasWord;
using namespace std;
class ModelTable: public QAbstractTableModel, public ArincParametrObserver
{
    Q_OBJECT
private:
    int rows;
    int columns;
    QHash<QModelIndex, QVariant> dat;
    QHash<int, QString> names_header;
    QVector<QString> visible_columns;
    QMap<int, ArincParametr*>::const_iterator iter;
    void setRowCount(int row);
    void setColumnCount(int column);
    int ColumnCountOfVisibleHeaders();
    int maxRowCount;
    //QAbstractItemModel interface
public:
    explicit ModelTable(int row,int column, QObject *parent = 0);
    explicit ModelTable(const ModelTable &table, QObject *parent=0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    ~ModelTable();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
signals:
    void changeContent();
public slots:
    void setVisibleHeader(bool visible,Parametr::Format f);
};

class ModelDiscrTable: public QAbstractTableModel, public ArincParametrObserver
{
    Q_OBJECT
private:
    int rows;
    int columns;
    int adress;
    QHash<QModelIndex, QVariant> dat;
    QHash<int, QString> names_header;
    QMap<int, ArincParametr*>::const_iterator iter;
    QStringList names_states;
    QStringList value_states;
    void setRowCount(int row);
    void setColumnCount(int column);
    int countOfStates;
public:
    explicit ModelDiscrTable(int adress, int row=0,int column=0, QObject *parent = 0);
    explicit ModelDiscrTable(const ModelDiscrTable &table, QObject *parent=0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setAdress(int adress);
    int getAdress()const;
    ~ModelDiscrTable();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
};
class MdiForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiForm(QWidget *parent = 0);
    explicit MdiForm(QString nameTitle, int index, QWidget *parent = 0);
    void setModel(ArincModelInterface *m);
    void addDiscrTable(int adress);
    void deleteDiscrTable(int adress);
    int index()const;
    ~MdiForm();
private:
    Ui::MdiForm *ui;
    ArincModelInterface *model;
    ModelTable *table;
    QMap<int, ModelDiscrTable*> discr_models;
    QMap<int, QTableView*> discr_tables;
    QMap<int, QVBoxLayout*> box_layout;
    QMap<int, QHBoxLayout*> labels_layout;
    QMap<int, QLabel*> labels;
    QMap<int, QLabelHasWord*> labelshasword;
    int i;//Индекс окна
public slots:
    void resizeTableToContent();
private slots:
    void on_splitter_splitterMoved(int pos, int index);
signals:
    void MdiFormDeleted(int index);
};
class QLabelHasWord: public QLabel, public ArincParametrObserver{
public:
    explicit QLabelHasWord(int adress, QWidget* parent);

    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
private:
    int adress;
};

#endif // MDIFORM_H
