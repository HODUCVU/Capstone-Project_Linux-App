#ifndef PROCESSCOMMAND_H
#define PROCESSCOMMAND_H
#include <QString>

class ProcessCommand
{
public:
    ProcessCommand();
    static QString execute(QString command);
};

#endif // PROCESSCOMMAND_H
