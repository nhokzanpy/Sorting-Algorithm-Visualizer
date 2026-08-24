#ifndef VISUALIZERPAGE_H
#define VISUALIZERPAGE_H

#include <QWidget>
#include <QTimer>
#include <vector>

#include "../models/sortingstep.h"
#include "../models/sortingstatistics.h"

class QLineEdit;
class QPushButton;
class QComboBox;
class QSlider;
class QLabel;

class SortingVisualizer;

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

    QLineEdit *m_inputEdit;
    QComboBox *m_algorithmCombo;

    QPushButton *m_randomButton;
    QPushButton *m_playButton;
    QPushButton *m_pauseButton;
    QPushButton *m_nextButton;
    QPushButton *m_resetButton;

    QSlider *m_speedSlider;

    QLabel *m_comparisonsLabel;
    QLabel *m_swapsLabel;
    QLabel *m_timeLabel;
    QLabel *m_statusLabel;

    SortingVisualizer *m_visualizer;

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