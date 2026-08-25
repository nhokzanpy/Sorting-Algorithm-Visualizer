#ifndef BENCHMARKPANEL_H
#define BENCHMARKPANEL_H

#include <QWidget>
#include <vector>

#include "../models/benchmarkresult.h"

class QTableWidget;

class BenchmarkPanel : public QWidget
{
    Q_OBJECT

public:
    explicit BenchmarkPanel(QWidget *parent = nullptr);

    void setResults(
        const std::vector<BenchmarkResult> &results
        );

    void clearResults();

private:
    QTableWidget *m_table;
};

#endif // BENCHMARKPANEL_H