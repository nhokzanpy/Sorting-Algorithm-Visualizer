#include "visualizerpage.h"

#include "../widgets/controlspanel.h"
#include "../widgets/sortingvisualizer.h"
#include "../widgets/statisticspanel.h"
#include "../widgets/benchmarkpanel.h"
#include "../algorithms/bubblesort.h"
#include "../algorithms/selectionsort.h"
#include "../algorithms/insertionsort.h"
#include "../algorithms/mergesort.h"
#include <QColor>
#include <QHBoxLayout>
#include <QLabel>
#include <QRandomGenerator>
#include <QStringList>
#include <QVBoxLayout>
#include "../benchmark/benchmarkrunner.h"

VisualizerPage::VisualizerPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();

    connect(
        &m_timer,
        &QTimer::timeout,
        this,
        &VisualizerPage::processNextStep
        );

    generateRandomData();
}


// =========================================================
// UI
// =========================================================

void VisualizerPage::setupUi()
{
    auto *mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        18,
        18,
        18,
        18
        );

    mainLayout->setSpacing(12);


    // =====================================================
    // Header
    // =====================================================

    auto *title =
        new QLabel(
            "Sorting Algorithm Visualizer"
            );

    title->setStyleSheet(
        "font-size: 30px;"
        "font-weight: 700;"
        "color: rgb(248, 250, 252);"
        );

    mainLayout->addWidget(
        title
        );


    auto *subtitle =
        new QLabel(
            "Basic Internal Sorting Algorithms Simulation"
            );

    subtitle->setStyleSheet(
        "color: rgb(148, 163, 184);"
        "font-size: 14px;"
        );

    mainLayout->addWidget(
        subtitle
        );

    mainLayout->addSpacing(6);


    // =====================================================
    // Controls
    // =====================================================

    m_controlsPanel =
        new ControlsPanel;

    mainLayout->addWidget(
        m_controlsPanel
        );


    // =====================================================
    // Visualizer Panel
    // =====================================================

    auto *visualizerContainer =
        new QWidget;

    visualizerContainer->setObjectName(
        "visualizerContainer"
        );

    visualizerContainer->setStyleSheet(
        "QWidget#visualizerContainer {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 12px;"
        "}"
        );


    auto *visualizerLayout =
        new QVBoxLayout(
            visualizerContainer
            );

    visualizerLayout->setContentsMargins(
        12,
        12,
        12,
        12
        );


    m_visualizer =
        new SortingVisualizer;


    visualizerLayout->addWidget(
        m_visualizer
        );


    mainLayout->addWidget(
        visualizerContainer,
        1
        );


    // =====================================================
    // Legend
    // =====================================================

    auto *legendLayout =
        new QHBoxLayout;

    legendLayout->setSpacing(18);


    auto createLegendItem =
        [](const QString &text,
           const QColor &color)
    {
        auto *container =
            new QWidget;

        auto *layout =
            new QHBoxLayout(
                container
                );

        layout->setContentsMargins(
            0,
            0,
            0,
            0
            );

        layout->setSpacing(6);


        auto *colorBox =
            new QLabel;

        colorBox->setFixedSize(
            12,
            12
            );

        colorBox->setStyleSheet(
            QString(
                "background-color: rgb(%1, %2, %3);"
                "border-radius: 3px;"
                )
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue())
            );


        auto *label =
            new QLabel(
                text
                );

        label->setStyleSheet(
            "color: rgb(148, 163, 184);"
            "font-size: 12px;"
            );


        layout->addWidget(
            colorBox
            );

        layout->addWidget(
            label
            );


        return container;
    };


    legendLayout->addStretch();


    legendLayout->addWidget(
        createLegendItem(
            "Normal",
            QColor(
                100,
                116,
                139
                )
            )
        );


    legendLayout->addWidget(
        createLegendItem(
            "Comparing",
            QColor(
                245,
                158,
                11
                )
            )
        );


    legendLayout->addWidget(
        createLegendItem(
            "Swapping",
            QColor(
                239,
                68,
                68
                )
            )
        );

    legendLayout->addWidget(
        createLegendItem(
            "Merging",
            QColor(
                56,
                189,
                248
                )
            )
        );

    legendLayout->addWidget(
        createLegendItem(
            "Sorted",
            QColor(
                34,
                197,
                94
                )
            )
        );


    legendLayout->addStretch();


    mainLayout->addLayout(
        legendLayout
        );


    // =====================================================
    // Statistics + Status
    // =====================================================

    m_statisticsPanel =
        new StatisticsPanel;

    mainLayout->addWidget(
        m_statisticsPanel
        );

    m_benchmarkPanel =
        new BenchmarkPanel;

    mainLayout->addWidget(
        m_benchmarkPanel
        );

    // =====================================================
    // Signals
    // =====================================================

    connect(
        m_controlsPanel,
        &ControlsPanel::randomRequested,
        this,
        &VisualizerPage::generateRandomData
        );


    connect(
        m_controlsPanel,
        &ControlsPanel::playRequested,
        this,
        &VisualizerPage::startSorting
        );


    connect(
        m_controlsPanel,
        &ControlsPanel::pauseRequested,
        this,
        &VisualizerPage::pauseSorting
        );


    connect(
        m_controlsPanel,
        &ControlsPanel::nextRequested,
        this,
        &VisualizerPage::nextStep
        );


    connect(
        m_controlsPanel,
        &ControlsPanel::resetRequested,
        this,
        &VisualizerPage::resetSorting
        );
}


// =========================================================
// Random Data
// =========================================================

void VisualizerPage::generateRandomData()
{
    m_timer.stop();


    std::vector<int> data;


    for (int i = 0; i < 8; ++i)
    {
        data.push_back(
            QRandomGenerator::global()
                ->bounded(
                    1,
                    100
                    )
            );
    }


    QString text;


    for (int value : data)
    {
        if (!text.isEmpty())
        {
            text += ", ";
        }

        text +=
            QString::number(
                value
                );
    }


    m_controlsPanel->setInputText(
        text
        );


    m_originalData =
        data;


    m_visualizer->setData(
        m_originalData
        );


    m_steps.clear();

    m_currentStep = 0;

    m_benchmarkPanel->clearResults();
    m_displayComparisons = 0;
    m_displaySwaps = 0;
    m_displayMoves = 0;


    m_statistics.reset();


    updateStatistics();


    m_statisticsPanel->setStatus(
        "Ready"
        );
}


// =========================================================
// Input
// =========================================================

void VisualizerPage::loadInputData()
{
    m_originalData.clear();


    const QStringList values =
        m_controlsPanel
            ->inputText()
            .split(
                ',',
                Qt::SkipEmptyParts
                );


    for (const QString &value : values)
    {
        bool ok = false;


        const int number =
            value
                .trimmed()
                .toInt(
                    &ok
                    );


        if (ok)
        {
            m_originalData.push_back(
                number
                );
        }
    }
}


// =========================================================
// Start Sorting
// =========================================================

void VisualizerPage::startSorting()
{
    loadInputData();


    if (m_originalData.empty())
    {
        m_statisticsPanel->setStatus(
            "Invalid input"
            );

        return;
    }


    if (m_steps.empty())
    {
        const QString algorithm =
            m_controlsPanel
                ->selectedAlgorithm();


        if (algorithm == "Bubble Sort")
        {
            m_steps =
                BubbleSort::sort(
                    m_originalData,
                    m_statistics
                    );
        }
        else if (
            algorithm ==
            "Selection Sort"
            )
        {
            m_steps =
                SelectionSort::sort(
                    m_originalData,
                    m_statistics
                    );
        }
        else if (
            algorithm ==
            "Insertion Sort"
            )
        {
            m_steps =
                InsertionSort::sort(
                    m_originalData,
                    m_statistics
                    );
        }
        else if (
            algorithm ==
            "Merge Sort"
            )
        {
            m_steps =
                MergeSort::sort(
                    m_originalData,
                    m_statistics
                    );
        }


        m_currentStep = 0;


        m_displayComparisons = 0;
        m_displaySwaps = 0;
        m_displayMoves = 0;


        m_visualizer->setData(
            m_originalData
            );


        updateStatistics();
    }

    const std::vector<BenchmarkResult> benchmarkResults =
        BenchmarkRunner::run(
            m_originalData
            );

    m_benchmarkPanel->setResults(
        benchmarkResults
        );

    const int delay =
        850 -
        m_controlsPanel
            ->speedValue();


    m_timer.start(
        delay
        );
}


// =========================================================
// Pause
// =========================================================

void VisualizerPage::pauseSorting()
{
    m_timer.stop();


    m_statisticsPanel->setStatus(
        "Paused"
        );
}


// =========================================================
// Next Step
// =========================================================

void VisualizerPage::nextStep()
{
    m_timer.stop();


    if (m_steps.empty())
    {
        startSorting();

        m_timer.stop();
    }


    processNextStep();
}


// =========================================================
// Reset
// =========================================================

void VisualizerPage::resetSorting()
{
    m_timer.stop();


    loadInputData();


    m_steps.clear();

    m_currentStep = 0;

    m_benchmarkPanel->clearResults();
    m_displayComparisons = 0;
    m_displaySwaps = 0;
    m_displayMoves = 0;


    m_statistics.reset();


    m_visualizer->setData(
        m_originalData
        );


    updateStatistics();


    m_statisticsPanel->setStatus(
        "Ready"
        );
}


// =========================================================
// Process Next Step
// =========================================================

void VisualizerPage::processNextStep()
{
    if (
        m_currentStep >=
        static_cast<int>(
            m_steps.size()
            )
        )
    {
        m_timer.stop();


        m_statisticsPanel->setStatus(
            "Sorting complete"
            );


        return;
    }


    const SortingStep &step =
        m_steps[
            m_currentStep
    ];


    if (
        step.type ==
        SortingStepType::Compare
        )
    {
        ++m_displayComparisons;
    }
    else if (
        step.type ==
        SortingStepType::Swap
        )
    {
        ++m_displaySwaps;

        m_displayMoves += 3;
    }
    else if (
        step.type ==
        SortingStepType::Move
        )
    {
        ++m_displayMoves;
    }


    m_visualizer->showStep(
        step
        );


    updateStatistics();


    m_statisticsPanel->setStatus(
        QString(
            "Step %1 / %2 - %3"
            )
            .arg(
                m_currentStep + 1
                )
            .arg(
                m_steps.size()
                )
            .arg(
                QString::fromStdString(
                    step.description
                    )
                )
        );


    ++m_currentStep;
}


// =========================================================
// Statistics
// =========================================================

void VisualizerPage::updateStatistics()
{
    m_statisticsPanel->setComparisons(
        m_displayComparisons
        );


    m_statisticsPanel->setSwaps(
        m_displaySwaps
        );


    m_statisticsPanel->setMoves(
        m_displayMoves
        );


    m_statisticsPanel->setTime(
        m_statistics.executionTimeMs
        );
}