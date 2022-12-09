#ifndef __ADJCONVERTER_H
#define __ADJCONVERTER_H

#include <QObject>
#include <qjsonobject.h>

class ADTJsonConverter
{
public:
    static QJsonObject propertyToJson(QObject *obj, QString objectName);

    static void JSonToObject(QObject *obj, QJsonObject *json, QString objectName);
};

#endif //__ADJCONVERTER_H
