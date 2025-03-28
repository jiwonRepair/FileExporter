#include "SimpleFileExporter.h"
#include <QCoreApplication>
#include <QDebug>

SimpleFileExporter::SimpleFileExporter(QObject* parent)
    : QObject(parent), m_fileExporter(this)
{
}

void SimpleFileExporter::exportSignalHistoryToFile() {
    if (m_fileExporter.isInProgress()) {
        qDebug() << "⚠️ exporter busy";
        return;
    }

    m_cancelRequested.store(false);
    QString filename = QCoreApplication::applicationDirPath() + "/signal_history.txt";

    m_exportFuture = QtConcurrent::run([=]() {
        m_fileExporter.writeCsvAsync<int>(
            m_signalHistory,
            filename,
            [](const int& v) { return QString::number(v); },
            [this](int percent) {
                if (m_cancelRequested.load()) return;
                QMetaObject::invokeMethod(this, [=]() {
                    emit progressChanged(percent);
                }, Qt::QueuedConnection);
            },
            [this]() {
                if (m_cancelRequested.load()) {
                    QMetaObject::invokeMethod(this, [=]() {
                        emit saveCancelled();
                    }, Qt::QueuedConnection);
                } else {
                    QMetaObject::invokeMethod(this, [=]() {
                        emit saveFinished();
                    }, Qt::QueuedConnection);
                }
            }
        );
    });

    m_exportWatcher.setFuture(m_exportFuture);
}

void SimpleFileExporter::cancelExport() {
    if (m_exportFuture.isRunning()) {
        m_cancelRequested.store(true);
        qDebug() << "❗ 저장 취소 요청됨";
    }
}
