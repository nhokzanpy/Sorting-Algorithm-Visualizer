#include "multisizebenchmarkpanel.h"

#include "../benchmark/multisizebenchmarkrunner.h"

#include <algorithm>
#include <cmath>

#include <QAbstractItemView>
#include <QColor>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>


// =========================================================
// Performance Chart
// =========================================================

class PerformanceChart : public QWidget
{
public:
    explicit PerformanceChart(
        QWidget *parent = nullptr
        )
        : QWidget(parent)
    {
        setMinimumHeight(
            210
            );
    }


    void setResults(
        const std::vector<MultiSizeBenchmarkResult> &results
        )
    {
        m_results =
            results;

        update();
    }


    void clearResults()
    {
        m_results.clear();

        update();
    }


protected:
    void paintEvent(
        QPaintEvent *
        ) override
    {
        QPainter painter(
            this
            );

        painter.setRenderHint(
            QPainter::Antialiasing
            );


        // =================================================
        // Background
        // =================================================

        painter.fillRect(
            rect(),
            QColor(
                17,
                24,
                39
                )
            );


        if (
            m_results.empty()
            )
        {
            painter.setPen(
                QColor(
                    100,
                    116,
                    139
                    )
                );

            painter.drawText(
                rect(),
                Qt::AlignCenter,
                "Run benchmark to display chart"
                );

            return;
        }


        // =================================================
        // Chart Area
        // =================================================

        const int left =
            52;

        const int right =
            18;

        const int top =
            28;

        const int bottom =
            34;


        const QRectF chartRect(
            left,
            top,
            width() -
                left -
                right,
            height() -
                top -
                bottom
            );


        painter.setPen(
            QColor(
                148,
                163,
                184
                )
            );


        painter.drawText(
            QRectF(
                left,
                3,
                width() -
                    left,
                20
                ),
            Qt::AlignLeft |
                Qt::AlignVCenter,
            "Time vs Input Size"
            );


        // =================================================
        // Collect Sizes / Time Range
        // =================================================

        std::vector<int> sizes;

        double maxTime =
            0.0;

        double minPositiveTime =
            -1.0;


        for (
            const MultiSizeBenchmarkResult &result :
            m_results
            )
        {
            if (
                std::find(
                    sizes.begin(),
                    sizes.end(),
                    result.inputSize
                    ) ==
                sizes.end()
                )
            {
                sizes.push_back(
                    result.inputSize
                    );
            }


            maxTime =
                std::max(
                    maxTime,
                    result.executionTimeMs
                    );


            if (
                result.executionTimeMs >
                0.0
                )
            {
                if (
                    minPositiveTime <
                    0.0
                    )
                {
                    minPositiveTime =
                        result.executionTimeMs;
                }
                else
                {
                    minPositiveTime =
                        std::min(
                            minPositiveTime,
                            result.executionTimeMs
                            );
                }
            }
        }


        std::sort(
            sizes.begin(),
            sizes.end()
            );


        if (
            maxTime <=
            0.0
            )
        {
            maxTime =
                1.0;
        }


        if (
            minPositiveTime <=
            0.0
            )
        {
            minPositiveTime =
                0.000001;
        }


        // =================================================
        // Log Scale
        // =================================================

        double minLog =
            std::log10(
                std::max(
                    minPositiveTime,
                    0.000001
                    )
                );


        double maxLog =
            std::log10(
                std::max(
                    maxTime,
                    0.000001
                    )
                );


        if (
            std::abs(
                maxLog -
                minLog
                ) <
            0.001
            )
        {
            maxLog =
                minLog +
                1.0;
        }


        // =================================================
        // Horizontal Grid
        // =================================================

        const int horizontalLines =
            5;


        for (
            int i = 0;
            i <= horizontalLines;
            ++i
            )
        {
            const double ratio =
                static_cast<double>(
                    i
                    ) /
                horizontalLines;


            const double y =
                chartRect.bottom() -
                ratio *
                    chartRect.height();


            painter.setPen(
                QColor(
                    51,
                    65,
                    85
                    )
                );


            painter.drawLine(
                QPointF(
                    chartRect.left(),
                    y
                    ),
                QPointF(
                    chartRect.right(),
                    y
                    )
                );


            const double logValue =
                minLog +
                ratio *
                    (
                        maxLog -
                        minLog
                        );


            const double value =
                std::pow(
                    10.0,
                    logValue
                    );


            painter.setPen(
                QColor(
                    100,
                    116,
                    139
                    )
                );


            painter.drawText(
                QRectF(
                    0,
                    y -
                        10,
                    left -
                        8,
                    20
                    ),
                Qt::AlignRight |
                    Qt::AlignVCenter,
                QString::number(
                    value,
                    'g',
                    3
                    )
                );
        }


        // =================================================
        // X Axis Labels
        // =================================================

        painter.setPen(
            QColor(
                148,
                163,
                184
                )
            );


        for (
            int index = 0;
            index <
            static_cast<int>(
                sizes.size()
                );
            ++index
            )
        {
            double x =
                chartRect.center().x();


            if (
                sizes.size() >
                1
                )
            {
                x =
                    chartRect.left() +
                    (
                        static_cast<double>(
                            index
                            ) /
                        (
                            sizes.size() -
                            1
                            )
                        ) *
                        chartRect.width();
            }


            painter.drawText(
                QRectF(
                    x -
                        35,
                    chartRect.bottom() +
                        6,
                    70,
                    20
                    ),
                Qt::AlignCenter,
                QString::number(
                    sizes[index]
                    )
                );
        }


        // =================================================
        // Algorithm Series
        // =================================================

        struct AlgorithmStyle
        {
            QString name;
            QColor color;
        };


        const std::vector<AlgorithmStyle> algorithms =
            {
                {
                    "Bubble Sort",
                    QColor(
                        96,
                        165,
                        250
                        )
                },

                {
                    "Selection Sort",
                    QColor(
                        250,
                        204,
                        21
                        )
                },

                {
                    "Insertion Sort",
                    QColor(
                        74,
                        222,
                        128
                        )
                },

                {
                    "Merge Sort",
                    QColor(
                        192,
                        132,
                        252
                        )
                }
            };


        for (
            const AlgorithmStyle &style :
            algorithms
            )
        {
            QPainterPath path;

            bool firstPoint =
                true;


            // =============================================
            // Lines
            // =============================================

            for (
                int index = 0;
                index <
                static_cast<int>(
                    sizes.size()
                    );
                ++index
                )
            {
                const int size =
                    sizes[index];


                const auto iterator =
                    std::find_if(
                        m_results.begin(),
                        m_results.end(),
                        [&](
                            const MultiSizeBenchmarkResult &result
                            )
                        {
                            return
                                result.algorithmName ==
                                    style.name &&
                                result.inputSize ==
                                    size;
                        }
                        );


                if (
                    iterator ==
                    m_results.end()
                    )
                {
                    continue;
                }


                double x =
                    chartRect.center().x();


                if (
                    sizes.size() >
                    1
                    )
                {
                    x =
                        chartRect.left() +
                        (
                            static_cast<double>(
                                index
                                ) /
                            (
                                sizes.size() -
                                1
                                )
                            ) *
                            chartRect.width();
                }


                const double time =
                    std::max(
                        iterator
                            ->executionTimeMs,
                        0.000001
                        );


                const double logTime =
                    std::log10(
                        time
                        );


                const double ratio =
                    (
                        logTime -
                        minLog
                        ) /
                    (
                        maxLog -
                        minLog
                        );


                const double y =
                    chartRect.bottom() -
                    ratio *
                        chartRect.height();


                if (
                    firstPoint
                    )
                {
                    path.moveTo(
                        x,
                        y
                        );

                    firstPoint =
                        false;
                }
                else
                {
                    path.lineTo(
                        x,
                        y
                        );
                }
            }


            painter.setPen(
                QPen(
                    style.color,
                    2.2
                    )
                );


            painter.drawPath(
                path
                );


            // =============================================
            // Points
            // =============================================

            painter.setBrush(
                style.color
                );


            for (
                int index = 0;
                index <
                static_cast<int>(
                    sizes.size()
                    );
                ++index
                )
            {
                const int size =
                    sizes[index];


                const auto iterator =
                    std::find_if(
                        m_results.begin(),
                        m_results.end(),
                        [&](
                            const MultiSizeBenchmarkResult &result
                            )
                        {
                            return
                                result.algorithmName ==
                                    style.name &&
                                result.inputSize ==
                                    size;
                        }
                        );


                if (
                    iterator ==
                    m_results.end()
                    )
                {
                    continue;
                }


                double x =
                    chartRect.center().x();


                if (
                    sizes.size() >
                    1
                    )
                {
                    x =
                        chartRect.left() +
                        (
                            static_cast<double>(
                                index
                                ) /
                            (
                                sizes.size() -
                                1
                                )
                            ) *
                            chartRect.width();
                }


                const double time =
                    std::max(
                        iterator
                            ->executionTimeMs,
                        0.000001
                        );


                const double ratio =
                    (
                        std::log10(
                            time
                            ) -
                        minLog
                        ) /
                    (
                        maxLog -
                        minLog
                        );


                const double y =
                    chartRect.bottom() -
                    ratio *
                        chartRect.height();


                painter.drawEllipse(
                    QPointF(
                        x,
                        y
                        ),
                    4.0,
                    4.0
                    );
            }
        }
    }


private:
    std::vector<MultiSizeBenchmarkResult>
        m_results;
};


// =========================================================
// Multi-size Benchmark Panel
// =========================================================

MultiSizeBenchmarkPanel::MultiSizeBenchmarkPanel(
    QWidget *parent
    )
    : QWidget(parent)
{
    auto *mainLayout =
        new QVBoxLayout(
            this
            );


    mainLayout->setContentsMargins(
        12,
        12,
        12,
        10
        );


    mainLayout->setSpacing(
        10
        );


    // =====================================================
    // Header
    // =====================================================

    auto *title =
        new QLabel(
            "Multi-size Benchmark"
            );


    title->setStyleSheet(
        "font-size: 16px;"
        "font-weight: 700;"
        "color: rgb(226, 232, 240);"
        );


    mainLayout->addWidget(
        title
        );


    // =====================================================
    // Controls
    // =====================================================

    auto *controlsLayout =
        new QHBoxLayout;


    controlsLayout->setSpacing(
        8
        );


    auto *presetLabel =
        new QLabel(
            "Preset Sizes:"
            );


    m_size10Button =
        new QPushButton(
            "10"
            );


    m_size50Button =
        new QPushButton(
            "50"
            );


    m_size100Button =
        new QPushButton(
            "100"
            );


    m_size500Button =
        new QPushButton(
            "500"
            );


    m_size1000Button =
        new QPushButton(
            "1000"
            );


    const std::vector<QPushButton *> sizeButtons =
        {
            m_size10Button,
            m_size50Button,
            m_size100Button,
            m_size500Button,
            m_size1000Button
        };


    for (
        QPushButton *button :
        sizeButtons
        )
    {
        button->setCheckable(
            true
            );


        button->setMinimumHeight(
            34
            );


        button->setMinimumWidth(
            54
            );
    }


    // =====================================================
    // Default Presets
    // =====================================================

    m_size10Button
        ->setChecked(
            true
            );


    m_size50Button
        ->setChecked(
            true
            );


    m_size100Button
        ->setChecked(
            true
            );


    m_size500Button
        ->setChecked(
            true
            );


    m_size1000Button
        ->setChecked(
            true
            );


    auto *customLabel =
        new QLabel(
            "Custom Sizes:"
            );


    m_customSizesEdit =
        new QLineEdit;


    m_customSizesEdit
        ->setPlaceholderText(
            "200, 2000, 5000"
            );


    m_customSizesEdit
        ->setMinimumHeight(
            34
            );


    m_runButton =
        new QPushButton(
            "Run Benchmark"
            );


    m_runButton
        ->setMinimumHeight(
            34
            );


    m_clearButton =
        new QPushButton(
            "Clear"
            );


    m_clearButton
        ->setMinimumHeight(
            34
            );


    controlsLayout->addWidget(
        presetLabel
        );


    controlsLayout->addWidget(
        m_size10Button
        );


    controlsLayout->addWidget(
        m_size50Button
        );


    controlsLayout->addWidget(
        m_size100Button
        );


    controlsLayout->addWidget(
        m_size500Button
        );


    controlsLayout->addWidget(
        m_size1000Button
        );


    controlsLayout->addSpacing(
        10
        );


    controlsLayout->addWidget(
        customLabel
        );


    controlsLayout->addWidget(
        m_customSizesEdit,
        1
        );


    controlsLayout->addWidget(
        m_runButton
        );


    controlsLayout->addWidget(
        m_clearButton
        );


    mainLayout->addLayout(
        controlsLayout
        );


    // =====================================================
    // Chart + Results Table
    // =====================================================

    auto *contentLayout =
        new QHBoxLayout;


    contentLayout->setSpacing(
        10
        );


    // =====================================================
    // Performance Chart
    // =====================================================

    m_chart =
        new PerformanceChart;


    m_chart->setStyleSheet(
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 10px;"
        );


    contentLayout->addWidget(
        m_chart,
        1
        );


    // =====================================================
    // Benchmark Results Table
    // =====================================================

    m_table =
        new QTableWidget;


    m_table->setColumnCount(
        6
        );


    m_table->setHorizontalHeaderLabels(
        {
            "Algorithm",
            "n",
            "Comparisons",
            "Swaps",
            "Moves",
            "Time (ms)"
        }
        );


    m_table->setRowCount(
        0
        );


    m_table->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );


    m_table->setSelectionMode(
        QAbstractItemView::NoSelection
        );


    m_table->verticalHeader()
        ->setVisible(
            false
            );


    m_table->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );


    m_table->verticalHeader()
        ->setDefaultSectionSize(
            30
            );


    m_table->setMinimumHeight(
        210
        );


    m_table->setStyleSheet(
        "QTableWidget {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 10px;"
        "gridline-color: rgb(51, 65, 85);"
        "color: rgb(226, 232, 240);"
        "font-size: 11px;"
        "}"
        "QTableWidget::item {"
        "padding: 5px;"
        "}"
        "QHeaderView::section {"
        "background-color: rgb(30, 41, 59);"
        "color: rgb(203, 213, 225);"
        "border: none;"
        "border-bottom: 1px solid rgb(51, 65, 85);"
        "padding: 6px;"
        "font-weight: 600;"
        "}"
        );


    contentLayout->addWidget(
        m_table,
        1
        );


    mainLayout->addLayout(
        contentLayout
        );


    // =====================================================
    // Footer: Legend + Status
    // =====================================================

    auto *footerLayout =
        new QHBoxLayout;


    footerLayout->setContentsMargins(
        4,
        0,
        4,
        0
        );


    footerLayout->setSpacing(
        18
        );


    auto createLegend =
        [](
            const QString &name,
            const QColor &color
            )
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


        layout->setSpacing(
            6
            );


        auto *dot =
            new QLabel;


        dot->setFixedSize(
            8,
            8
            );


        dot->setStyleSheet(
            QString(
                "background-color: "
                "rgb(%1,%2,%3);"
                "border-radius: 4px;"
                )
                .arg(
                    color.red()
                    )
                .arg(
                    color.green()
                    )
                .arg(
                    color.blue()
                    )
            );


        auto *label =
            new QLabel(
                name
                );


        label->setStyleSheet(
            "color: rgb(203, 213, 225);"
            "font-size: 11px;"
            );


        layout->addWidget(
            dot
            );


        layout->addWidget(
            label
            );


        return container;
    };


    footerLayout->addWidget(
        createLegend(
            "Bubble",
            QColor(
                96,
                165,
                250
                )
            )
        );


    footerLayout->addWidget(
        createLegend(
            "Selection",
            QColor(
                250,
                204,
                21
                )
            )
        );


    footerLayout->addWidget(
        createLegend(
            "Insertion",
            QColor(
                74,
                222,
                128
                )
            )
        );


    footerLayout->addWidget(
        createLegend(
            "Merge",
            QColor(
                192,
                132,
                252
                )
            )
        );


    // Push status to far right
    footerLayout->addStretch();


    m_statusLabel =
        new QLabel(
            "Multi-size performance testing ready"
            );


    m_statusLabel->setAlignment(
        Qt::AlignRight |
        Qt::AlignVCenter
        );


    m_statusLabel->setStyleSheet(
        "color: rgb(96, 165, 250);"
        "font-size: 12px;"
        );


    footerLayout->addWidget(
        m_statusLabel
        );


    mainLayout->addLayout(
        footerLayout
        );


    // =====================================================
    // General Styling
    // =====================================================

    setStyleSheet(
        "QLabel {"
        "color: rgb(203, 213, 225);"
        "}"
        "QLineEdit {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(71, 85, 105);"
        "border-radius: 7px;"
        "padding: 6px 8px;"
        "color: rgb(226, 232, 240);"
        "}"
        "QLineEdit:focus {"
        "border: 1px solid rgb(96, 165, 250);"
        "}"
        "QPushButton {"
        "background-color: rgb(30, 41, 59);"
        "border: 1px solid rgb(71, 85, 105);"
        "border-radius: 7px;"
        "padding: 6px 10px;"
        "color: rgb(226, 232, 240);"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(51, 65, 85);"
        "}"
        "QPushButton:checked {"
        "background-color: rgb(37, 99, 235);"
        "border: 1px solid rgb(96, 165, 250);"
        "color: white;"
        "}"
        );


    // =====================================================
    // Signals
    // =====================================================

    connect(
        m_runButton,
        &QPushButton::clicked,
        this,
        &MultiSizeBenchmarkPanel::runBenchmark
        );


    connect(
        m_clearButton,
        &QPushButton::clicked,
        this,
        &MultiSizeBenchmarkPanel::clearResults
        );


    connect(
        m_customSizesEdit,
        &QLineEdit::returnPressed,
        this,
        &MultiSizeBenchmarkPanel::runBenchmark
        );
}


// =========================================================
// Selected Sizes
// =========================================================

std::vector<int>
MultiSizeBenchmarkPanel::selectedSizes() const
{
    std::vector<int> sizes;


    auto addSize =
        [&sizes](
            int value
            )
    {
        if (
            value <=
            0
            )
        {
            return;
        }


        if (
            std::find(
                sizes.begin(),
                sizes.end(),
                value
                ) ==
            sizes.end()
            )
        {
            sizes.push_back(
                value
                );
        }
    };


    if (
        m_size10Button
            ->isChecked()
        )
    {
        addSize(
            10
            );
    }


    if (
        m_size50Button
            ->isChecked()
        )
    {
        addSize(
            50
            );
    }


    if (
        m_size100Button
            ->isChecked()
        )
    {
        addSize(
            100
            );
    }


    if (
        m_size500Button
            ->isChecked()
        )
    {
        addSize(
            500
            );
    }


    if (
        m_size1000Button
            ->isChecked()
        )
    {
        addSize(
            1000
            );
    }


    const QStringList customParts =
        m_customSizesEdit
            ->text()
            .split(
                ',',
                Qt::SkipEmptyParts
                );


    for (
        const QString &part :
        customParts
        )
    {
        bool ok =
            false;


        const int value =
            part
                .trimmed()
                .toInt(
                    &ok
                    );


        if (
            ok
            )
        {
            addSize(
                value
                );
        }
    }


    std::sort(
        sizes.begin(),
        sizes.end()
        );


    return sizes;
}


// =========================================================
// Run Benchmark
// =========================================================

void MultiSizeBenchmarkPanel::runBenchmark()
{
    const std::vector<int> sizes =
        selectedSizes();


    if (
        sizes.empty()
        )
    {
        m_statusLabel->setText(
            "Select or enter at least one valid input size."
            );

        return;
    }


    m_statusLabel->setText(
        "Running benchmark..."
        );


    const std::vector<MultiSizeBenchmarkResult> results =
        MultiSizeBenchmarkRunner::run(
            sizes
            );


    showResults(
        results
        );


    m_statusLabel->setText(
        QString(
            "Benchmark complete - %1 sizes, %2 results"
            )
            .arg(
                sizes.size()
                )
            .arg(
                results.size()
                )
        );
}


// =========================================================
// Show Results
// =========================================================

void MultiSizeBenchmarkPanel::showResults(
    const std::vector<MultiSizeBenchmarkResult> &results
    )
{
    m_table->setRowCount(
        static_cast<int>(
            results.size()
            )
        );


    for (
        int row = 0;
        row <
        static_cast<int>(
            results.size()
            );
        ++row
        )
    {
        const MultiSizeBenchmarkResult &result =
            results[row];


        m_table->setItem(
            row,
            0,
            new QTableWidgetItem(
                result.algorithmName
                )
            );


        m_table->setItem(
            row,
            1,
            new QTableWidgetItem(
                QString::number(
                    result.inputSize
                    )
                )
            );


        m_table->setItem(
            row,
            2,
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.comparisons
                        )
                    )
                )
            );


        m_table->setItem(
            row,
            3,
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.swaps
                        )
                    )
                )
            );


        m_table->setItem(
            row,
            4,
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.moves
                        )
                    )
                )
            );


        m_table->setItem(
            row,
            5,
            new QTableWidgetItem(
                QString::number(
                    result.executionTimeMs,
                    'f',
                    4
                    )
                )
            );
    }


    m_chart->setResults(
        results
        );
}


// =========================================================
// Clear
// =========================================================

void MultiSizeBenchmarkPanel::clearResults()
{
    m_table->setRowCount(
        0
        );


    m_chart->clearResults();


    m_statusLabel->setText(
        "Multi-size performance testing ready"
        );
}