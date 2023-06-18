#ifndef ADTAPP_H
#define ADTAPP_H

#include "../core/treemodel.h"

#include <QApplication>

class ADTAppPrivate;

class ADTApp
{
public:
    ADTApp(QApplication *application);
    ~ADTApp();

    int runApp();

private:
    void buildModel();

private:
    ADTAppPrivate *d;

private:
    ADTApp(const ADTApp &) = delete;
    ADTApp(ADTApp &&)      = delete;
    ADTApp &operator=(const ADTApp &) = delete;
    ADTApp &operator=(ADTApp &&) = delete;
};

#endif // ADTAPP_H
