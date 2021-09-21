#ifndef PROCESSHELPER_H
#define PROCESSHELPER_H

#include <QString>



class ProcessHelper
{
public:
    struct Output
    {
    public:
        QString stdOut;
        QString stdErr;
        int exitCode;
        QString ToString();
    };

    static Output Execute(const QString& cmd);
};

#endif // PROCESSHELPER_H
