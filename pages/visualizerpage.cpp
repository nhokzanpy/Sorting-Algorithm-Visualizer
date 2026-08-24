#include "visualizerpage.h"

#include "../widgets/sortingvisualizer.h"
#include "../algorithms/bubblesort.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QRandomGenerator>
#include <QColor>

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

void VisualizerPage::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        18,
        18,
        18,
        18
        );

    mainLayout->setSpacing(
        12
        );

    auto *title = new QLabel("Sorting Algorithm Visualizer");

    title->setStyleSheet(
        "font-size: 30px;"
        "font-weight: 700;"
        "color: rgb(248, 250, 252);"
        );

    mainLayout->addWidget(title);

    auto *subtitle =
        new QLabel("Basic Internal Sorting Algorithms Simulation");

    subtitle->setStyleSheet(
        "color: rgb(148, 163, 184);"
        "font-size: 14px;"
        );

    mainLayout->addWidget(subtitle);

    mainLayout->addSpacing(6);

    auto *inputLabel = new QLabel("Input Data");

    inputLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(inputLabel);

    auto *inputLayout = new QHBoxLayout;

    inputLayout->setSpacing(10);

    m_inputEdit = new QLineEdit;
    m_randomButton = new QPushButton("Random");

    inputLayout->addWidget(m_inputEdit);
    inputLayout->addWidget(m_randomButton);

    mainLayout->addLayout(inputLayout);

    auto *controlsLayout = new QHBoxLayout;

    auto *algorithmLabel = new QLabel("Algorithm");

    algorithmLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(algorithmLabel);

    controlsLayout->setSpacing(10);

    m_algorithmCombo = new QComboBox;
    m_algorithmCombo->addItem("Bubble Sort");

    m_playButton = new QPushButton("Play");
    m_pauseButton = new QPushButton("Pause");
    m_nextButton = new QPushButton("Next");
    m_resetButton = new QPushButton("Reset");

    m_playButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(37, 99, 235);"
        "border: 1px solid rgb(59, 130, 246);"
        "color: white;"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(59, 130, 246);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(29, 78, 216);"
        "}"
        );

    m_resetButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(194, 65, 12);"
        "border: 1px solid rgb(234, 88, 12);"
        "color: white;"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(234, 88, 12);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(154, 52, 18);"
        "}"
        );

    controlsLayout->addWidget(m_algorithmCombo);
    controlsLayout->addWidget(m_playButton);
    controlsLayout->addWidget(m_pauseButton);
    controlsLayout->addWidget(m_nextButton);
    controlsLayout->addWidget(m_resetButton);

    mainLayout->addLayout(controlsLayout);

    auto *speedLayout = new QHBoxLayout;

    auto *speedLabel = new QLabel("Speed");

    speedLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(speedLabel);

    speedLayout->setSpacing(8);

    speedLayout->addWidget(new QLabel("Slow"));

    m_speedSlider = new QSlider(Qt::Horizontal);
    m_speedSlider->setRange(50, 800);
    m_speedSlider->setValue(300);

    speedLayout->addWidget(m_speedSlider);
    speedLayout->addWidget(new QLabel("Fast"));

    mainLayout->addLayout(speedLayout);

    auto *visualizerContainer = new QWidget;

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
    auto *legendLayout = new QHBoxLayout;

    legendLayout->setSpacing(18);

    auto createLegendItem =
        [](const QString &text, const QColor &color)
    {
        auto *container = new QWidget;

        auto *layout = new QHBoxLayout(container);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(6);

        auto *colorBox = new QLabel;
        colorBox->setFixedSize(12, 12);

        colorBox->setStyleSheet(
            QString(
                "background-color: rgb(%1, %2, %3);"
                "border-radius: 3px;"
                )
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue())
            );

        auto *label = new QLabel(text);

        label->setStyleSheet(
            "color: rgb(148, 163, 184);"
            "font-size: 12px;"
            );

        layout->addWidget(colorBox);
        layout->addWidget(label);

        return container;
    };

    legendLayout->addStretch();

    legendLayout->addWidget(
        createLegendItem(
            "Normal",
            QColor(100, 116, 139)
            )
        );

    legendLayout->addWidget(
        createLegendItem(
            "Comparing",
            QColor(245, 158, 11)
            )
        );

    legendLayout->addWidget(
        createLegendItem(
            "Swapping",
            QColor(239, 68, 68)
            )
        );

    legendLayout->addWidget(
        createLegendItem(
            "Sorted",
            QColor(34, 197, 94)
            )
        );

    legendLayout->addStretch();

    mainLayout->addLayout(
        legendLayout
        );
    auto *statsLayout = new QHBoxLayout;

    statsLayout->setSpacing(12);

    m_comparisonsLabel =
        new QLabel("Comparisons: 0");

    m_swapsLabel =
        new QLabel("Swaps / Moves: 0");

    m_timeLabel =
        new QLabel("Time: 0 ms");

    const QString statCardStyle =
        "QLabel {"
        "background-color: rgb(30, 41, 59);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 10px;"
        "padding: 16px;"
        "font-size: 15px;"
        "font-weight: 600;"
        "}";

    m_comparisonsLabel->setStyleSheet(
        statCardStyle
        );

    m_swapsLabel->setStyleSheet(
        statCardStyle
        );

    m_timeLabel->setStyleSheet(
        statCardStyle
        );

    m_comparisonsLabel->setAlignment(
        Qt::AlignCenter
        );

    m_swapsLabel->setAlignment(
        Qt::AlignCenter
        );

    m_timeLabel->setAlignment(
        Qt::AlignCenter
        );

    statsLayout->addWidget(m_comparisonsLabel);
    statsLayout->addWidget(m_swapsLabel);
    statsLayout->addWidget(m_timeLabel);

    mainLayout->addLayout(statsLayout);

    m_statusLabel = new QLabel("Ready");

    m_statusLabel->setStyleSheet(
        "QLabel {"
        "background-color: rgb(30, 41, 59);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 8px;"
        "padding: 10px 12px;"
        "color: rgb(203, 213, 225);"
        "font-size: 14px;"
        "}"
        );

    mainLayout->addWidget(m_statusLabel);

    connect(
        m_randomButton,
        &QPushButton::clicked,
        this,
        &VisualizerPage::generateRandomData
        );

    connect(
        m_playButton,
        &QPushButton::clicked,
        this,
        &VisualizerPage::startSorting
        );

    connect(
        m_pauseButton,
        &QPushButton::clicked,
        this,
        &VisualizerPage::pauseSorting
        );

    connect(
        m_nextButton,
        &QPushButton::clicked,
        this,
        &VisualizerPage::nextStep
        );

    connect(
        m_resetButton,
        &QPushButton::clicked,
        this,
        &VisualizerPage::resetSorting
        );
}

void VisualizerPage::generateRandomData()
{
    std::vector<int> data;

    for (int i = 0; i < 8; ++i)
    {
        data.push_back(
            QRandomGenerator::global()->bounded(1, 100)
            );
    }

    QString text;

    for (int value : data)
    {
        if (!text.isEmpty())
        {
            text += ", ";
        }

        text += QString::number(value);
    }

    m_inputEdit->setText(text);

    m_originalData = data;

    m_visualizer->setData(data);

    m_steps.clear();
    m_currentStep = 0;

    m_displayComparisons = 0;
    m_displaySwaps = 0;
    m_displayMoves = 0;

    m_statistics.reset();

    updateStatistics();

    m_statusLabel->setText("Ready");
}

void VisualizerPage::loadInputData()
{
    m_originalData.clear();

    const QStringList values =
        m_inputEdit
            ->text()
            .split(',', Qt::SkipEmptyParts);

    for (const QString &value : values)
    {
        bool ok = false;

        const int number =
            value.trimmed().toInt(&ok);

        if (ok)
        {
            m_originalData.push_back(number);
        }
    }
}

void VisualizerPage::startSorting()
{
    loadInputData();

    if (m_originalData.empty())
    {
        m_statusLabel->setText("Invalid input");
        return;
    }

    if (m_steps.empty())
    {
        m_steps =
            BubbleSort::sort(
                m_originalData,
                m_statistics
                );

        m_currentStep = 0;

        updateStatistics();
    }

    const int delay =
        850 - m_speedSlider->value();

    m_timer.start(delay);
}

void VisualizerPage::pauseSorting()
{
    m_timer.stop();

    m_statusLabel->setText("Paused");
}

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

void VisualizerPage::resetSorting()
{
    m_timer.stop();

    loadInputData();

    m_steps.clear();
    m_currentStep = 0;

    m_displayComparisons = 0;
    m_displaySwaps = 0;
    m_displayMoves = 0;

    m_statistics.reset();

    m_visualizer->setData(m_originalData);

    updateStatistics();

    m_statusLabel->setText("Ready");
}

void VisualizerPage::processNextStep()
{
    if (
        m_currentStep >=
        static_cast<int>(m_steps.size())
        )
    {
        m_timer.stop();

        m_statusLabel->setText(
            "Sorting complete"
            );

        return;
    }

    const SortingStep &step =
        m_steps[m_currentStep];

    if (step.type == SortingStepType::Compare)
    {
        ++m_displayComparisons;
    }
    else if (step.type == SortingStepType::Swap)
    {
        ++m_displaySwaps;
        m_displayMoves += 3;
    }

    m_visualizer->showStep(step);

    updateStatistics();

    m_statusLabel->setText(
        QString("Step %1 / %2 - %3")
            .arg(m_currentStep + 1)
            .arg(m_steps.size())
            .arg(
                QString::fromStdString(
                    step.description
                    )
                )
        );

    ++m_currentStep;
}

void VisualizerPage::updateStatistics()
{
    m_comparisonsLabel->setText(
        "Comparisons: " +
        QString::number(
            m_displayComparisons
            )
        );

    m_swapsLabel->setText(
        "Swaps: " +
        QString::number(
            m_displaySwaps
            ) +
        " | Moves: " +
        QString::number(
            m_displayMoves
            )
        );

    m_timeLabel->setText(
        "Time: " +
        QString::number(
            m_statistics.executionTimeMs,
            'f',
            4
            ) +
        " ms"
        );
}