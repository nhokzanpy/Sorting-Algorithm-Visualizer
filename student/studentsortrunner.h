#ifndef STUDENTSORTRUNNER_H
#define STUDENTSORTRUNNER_H

#include <QString>
#include <vector>

#include "../models/studentsortresult.h"

class StudentSortRunner
{
public:
    static StudentSortResult run(
        const std::vector<int> &data,
        const QString &algorithmName
        );
};

#endif // STUDENTSORTRUNNER_H