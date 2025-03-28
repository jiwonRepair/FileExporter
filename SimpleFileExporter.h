#ifndef WIFI_OPTIMIZER_H
#define WIFI_OPTIMIZER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <atomic>
#include "LibuvFileExporter.h"

class WifiOptimizer : public QObject
{
    Q_OBJECT
public:
    explicit WifiOptimizer(QObject* parent = nullptr);

    Q_INVOKABLE void exportSignalHistoryToFile();
    Q_INVOKABLE void cancelExport();

signals:
    void progressChanged(int percent);
    void saveFinished();
    void saveCancelled();

private:
    QVector<int> m_signalHistory { 88, 70, 55, 40, 66, 80 };
    LibuvFileExporter m_fileExporter;

    QFuture<void> m_exportFuture;
    QFutureWatcher<void> m_exportWatcher;
    std::atomic_bool m_cancelRequested = false;
};

#endif // WIFI_OPTIMIZER_H