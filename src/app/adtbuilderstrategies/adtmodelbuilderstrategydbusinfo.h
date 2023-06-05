#ifndef ADTMODELBUILDERSTRATEGYDBUSINFO_H
#define ADTMODELBUILDERSTRATEGYDBUSINFO_H

#include "../core/treemodelbuilderinterface.h"
#include "adtmodelbuilderstrategyinterface.h"

#include <QDBusConnection>
#include <QDBusInterface>
class ADTModelBuilderStrategyDbusInfo : public ADTModelBuilderStrategyInterface
{
public:
    ADTModelBuilderStrategyDbusInfo(QString serviceName,
                                    QString path,
                                    QString interface,
                                    QString getMethodName,
                                    QString findInterface,
                                    TreeModelBuilderInterface *builder);

public:
    std::unique_ptr<TreeModel> buildModel();

    QStringList getObjectsPathByInterface(QString interface);

    QJsonDocument getInterfaceInfo(QString path);

private:
    QString m_serviceName;
    QString m_path;
    QString m_interface;
    QString m_get_method_name;
    QString m_findInterface;
    QString m_jsonArrayName = "objects";
    //QString m_signal          = "executor_stdout";
    //int m_mSeconds            = 10000;

    std::unique_ptr<TreeModelBuilderInterface> m_treeModelBuilder;

    QList<QString> m_implementedInterfacesPath;

    std::unique_ptr<QDBusConnection> m_dbus;
    std::unique_ptr<QDBusInterface> m_dbusInterface;
};

#endif // ADTMODELBUILDERSTRATEGYDBUSINFO_H
