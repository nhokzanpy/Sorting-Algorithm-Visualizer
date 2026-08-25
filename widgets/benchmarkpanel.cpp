#include "benchmarkpanel.h"

#include <algorithm>
#include <limits>

#include <QAbstractItemView>
#include <QColor>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>


BenchmarkPanel::BenchmarkPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        0,
        0,
        0,
        0
        );

    mainLayout->setSpacing(10);


    // =====================================================
    // Title
    // =====================================================

    auto *title =
        new QLabel(
            "Algorithm Benchmark"
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
    // Table
    // =====================================================

    m_table =
        new QTableWidget;

    m_table->setMinimumHeight(
        220
        );

    m_table->setColumnCount(
        5
        );

    m_table->setHorizontalHeaderLabels(
        {
            "Algorithm",
            "Comparisons",
            "Swaps",
            "Moves",
            "Time (ms)"
        }
        );

    m_table->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    m_table->setSelectionMode(
        QAbstractItemView::NoSelection
        );

    m_table->verticalHeader()
        ->setVisible(false);

    m_table->verticalHeader()
        ->setDefaultSectionSize(
            36
            );

    m_table->horizontalHeader()
        ->setMinimumHeight(
            38
            );

    m_table->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    m_table->setStyleSheet(
        "QTableWidget {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 10px;"
        "gridline-color: rgb(51, 65, 85);"
        "color: rgb(226, 232, 240);"
        "font-size: 13px;"
        "}"
        "QTableWidget::item {"
        "padding: 8px;"
        "}"
        "QHeaderView::section {"
        "background-color: rgb(30, 41, 59);"
        "color: rgb(203, 213, 225);"
        "border: none;"
        "border-bottom: 1px solid rgb(51, 65, 85);"
        "padding: 10px;"
        "font-size: 13px;"
        "font-weight: 600;"
        "}"
        );

    mainLayout->addWidget(
        m_table
        );
}


// =========================================================
// Results
// =========================================================

void BenchmarkPanel::setResults(
    const std::vector<BenchmarkResult> &results
    )
{
    m_table->setRowCount(
        static_cast<int>(
            results.size()
            )
        );


    if (results.empty())
    {
        return;
    }


    // =====================================================
    // Find Best Metrics
    // =====================================================

    std::size_t bestComparisons =
        std::numeric_limits<std::size_t>::max();

    std::size_t bestSwaps =
        std::numeric_limits<std::size_t>::max();

    std::size_t bestMoves =
        std::numeric_limits<std::size_t>::max();

    double bestTime =
        std::numeric_limits<double>::max();


    for (const BenchmarkResult &result : results)
    {
        bestComparisons =
            std::min(
                bestComparisons,
                result.comparisons
                );

        bestSwaps =
            std::min(
                bestSwaps,
                result.swaps
                );

        bestMoves =
            std::min(
                bestMoves,
                result.moves
                );

        bestTime =
            std::min(
                bestTime,
                result.executionTimeMs
                );
    }


    // =====================================================
    // Highlight Style
    // =====================================================

    const QColor bestBackground(
        20,
        83,
        45
        );

    const QColor bestText(
        134,
        239,
        172
        );


    // =====================================================
    // Populate Table
    // =====================================================

    for (
        int row = 0;
        row < static_cast<int>(
            results.size()
            );
        ++row
        )
    {
        const BenchmarkResult &result =
            results[row];


        auto *algorithmItem =
            new QTableWidgetItem(
                result.algorithmName
                );


        auto *comparisonsItem =
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.comparisons
                        )
                    )
                );


        auto *swapsItem =
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.swaps
                        )
                    )
                );


        auto *movesItem =
            new QTableWidgetItem(
                QString::number(
                    static_cast<qulonglong>(
                        result.moves
                        )
                    )
                );


        auto *timeItem =
            new QTableWidgetItem(
                QString::number(
                    result.executionTimeMs,
                    'f',
                    4
                    )
                );


        // =================================================
        // Highlight Best Values
        // =================================================

        if (
            result.comparisons ==
            bestComparisons
            )
        {
            comparisonsItem->setBackground(
                bestBackground
                );

            comparisonsItem->setForeground(
                bestText
                );
        }


        if (
            result.swaps ==
            bestSwaps
            )
        {
            swapsItem->setBackground(
                bestBackground
                );

            swapsItem->setForeground(
                bestText
                );
        }


        if (
            result.moves ==
            bestMoves
            )
        {
            movesItem->setBackground(
                bestBackground
                );

            movesItem->setForeground(
                bestText
                );
        }


        if (
            result.executionTimeMs ==
            bestTime
            )
        {
            timeItem->setBackground(
                bestBackground
                );

            timeItem->setForeground(
                bestText
                );
        }


        // =================================================
        // Add Items
        // =================================================

        m_table->setItem(
            row,
            0,
            algorithmItem
            );

        m_table->setItem(
            row,
            1,
            comparisonsItem
            );

        m_table->setItem(
            row,
            2,
            swapsItem
            );

        m_table->setItem(
            row,
            3,
            movesItem
            );

        m_table->setItem(
            row,
            4,
            timeItem
            );
    }
}


// =========================================================
// Clear
// =========================================================

void BenchmarkPanel::clearResults()
{
    m_table->setRowCount(
        0
        );
}