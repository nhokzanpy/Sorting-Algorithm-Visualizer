#ifndef VISUALIZERPAGE_H
#define VISUALIZERPAGE_H

#include <QWidget>
#include <QTimer>
#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"
class BenchmarkPanel;
class StatisticsPanel;
class SortingVisualizer;
class ControlsPanel;
class StudentPanel;
class VisualizerPage : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizerPage(QWidget *parent = nullptr);

private slots:
    void generateRandomData();
    void startSorting();
    void pauseSorting();
    void nextStep();
    void resetSorting();
    void processNextStep();

private:
    void setupUi();
    void loadInputData();
    void updateStatistics();

    ControlsPanel *m_controlsPanel;

    StatisticsPanel *m_statisticsPanel;

    BenchmarkPanel *m_benchmarkPanel;

    SortingVisualizer *m_visualizer;

    StudentPanel *m_studentPanel;

    QTimer m_timer;

    std::vector<int> m_originalData;
    std::vector<SortingStep> m_steps;

    SortingStatistics m_statistics;

    int m_currentStep = 0;

    std::size_t m_displayComparisons = 0;
    std::size_t m_displaySwaps = 0;
    std::size_t m_displayMoves = 0;
};

#endif // VISUALIZERPAGE_H