#include "processhelper.h"

#include <QProcess>
#include <QApplication>

ProcessHelper::Output ProcessHelper::Execute(const QString& cmd){
    auto fn = qApp->applicationDirPath();

    QProcess process;
    process.setWorkingDirectory(fn);
    process.start(cmd);
    process.waitForFinished(-1); // will wait forever until finished
    ProcessHelper::Output a {process.readAllStandardOutput(),
                      process.readAllStandardError(),
                      process.exitCode()};
    return a;
}

auto ProcessHelper::Output::ToString() -> QString
{
    QString e;
    static const QString SEPARATOR = QStringLiteral("\n\n");

    if(!stdOut.isEmpty())
    {
        if(!e.isEmpty()) { e+=SEPARATOR;
        }
        e+="stdout: "+stdOut;
    }
    if(!stdErr.isEmpty())
    {
        if(!e.isEmpty()) e+=SEPARATOR;
        e+="stderr: "+stdErr;
    }
    if(!e.isEmpty()) e+=SEPARATOR;
    e+=QStringLiteral("exitCode: %1").arg(exitCode);
    return e;
}
