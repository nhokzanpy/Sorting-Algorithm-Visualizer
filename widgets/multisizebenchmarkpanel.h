#ifndef MULTISIZEBENCHMARKPANEL_H
#define MULTISIZEBENCHMARKPANEL_H

#include <QWidget>
#include <vector>

#include "../models/multisizebenchmarkresult.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
class PerformanceChart;


class MultiSizeBenchmarkPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MultiSizeBenchmarkPanel(
        QWidget *parent = nullptr
        );

private slots:
    void runBenchmark();
    void clearResults();

private:
    std::vector<int> selectedSizes() const;

    void showResults(
        const std::vector<MultiSizeBenchmarkResult> &results
        );

    QPushButton *m_size10Button;
    QPushButton *m_size50Button;
    QPushButton *m_size100Button;
    QPushButton *m_size500Button;
    QPushButton *m_size1000Button;

    QLineEdit *m_customSizesEdit;

    QPushButton *m_runButton;
    QPushButton *m_clearButton;

    PerformanceChart *m_chart;

    QTableWidget *m_table;

    QLabel *m_statusLabel;
};

#endif // MULTISIZEBENCHMARKPANEL_H