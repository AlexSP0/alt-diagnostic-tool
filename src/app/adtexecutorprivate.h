#ifndef ADTEXECUTORPRIVATE_H
#define ADTEXECUTORPRIVATE_H

#include <statuscommonwidget.h>
#include <vector>
#include <QDBusConnection>
#include <qdbusinterface.h>

class ADTExecutorPrivate
{
public:
    ADTExecutorPrivate(std::vector<StatusCommonWidget *> *vectorWidgets);

    std::vector<StatusCommonWidget *> *widgets;

    QString serviceName;
    QString path;
    QString interfaceName;

    volatile bool stopFlag;

    std::unique_ptr<QDBusConnection> dbus;
    std::unique_ptr<QDBusInterface> dbusInterface;

private:
    ADTExecutorPrivate(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate(ADTExecutorPrivate &&)      = delete;
    ADTExecutorPrivate &operator=(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate &operator=(ADTExecutorPrivate &&) = delete;
};

#endif // ADTEXECUTORPRIVATE_H
