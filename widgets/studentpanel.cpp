#include "studentpanel.h"

#include "../student/studentsortrunner.h"

#include <QAbstractItemView>
#include <QComboBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>


namespace
{
constexpr int MaxHistoryRows = 3;
}


StudentPanel::StudentPanel(QWidget *parent)
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

    mainLayout->setSpacing(
        10
        );


    // =====================================================
    // Title
    // =====================================================

    auto *title =
        new QLabel(
            "Student Lab"
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
    // Input Controls
    // =====================================================

    auto *inputLayout =
        new QHBoxLayout;

    inputLayout->setSpacing(
        8
        );


    m_inputEdit =
        new QLineEdit;

    m_inputEdit->setPlaceholderText(
        "Enter numbers: 8, 3, 5, 1, 9"
        );

    m_inputEdit->setMinimumHeight(
        36
        );


    m_algorithmCombo =
        new QComboBox;

    m_algorithmCombo->addItems(
        {
            "Bubble Sort",
            "Selection Sort",
            "Insertion Sort",
            "Merge Sort"
        }
        );

    m_algorithmCombo->setMinimumHeight(
        36
        );

    m_algorithmCombo->setMinimumWidth(
        125
        );


    m_sortButton =
        new QPushButton(
            "Sort"
            );

    m_sortButton->setMinimumHeight(
        36
        );

    m_sortButton->setMinimumWidth(
        68
        );


    m_clearButton =
        new QPushButton(
            "Clear"
            );

    m_clearButton->setMinimumHeight(
        36
        );

    m_clearButton->setMinimumWidth(
        68
        );


    inputLayout->addWidget(
        m_inputEdit,
        1
        );

    inputLayout->addWidget(
        m_algorithmCombo
        );

    inputLayout->addWidget(
        m_sortButton
        );

    inputLayout->addWidget(
        m_clearButton
        );


    mainLayout->addLayout(
        inputLayout
        );


    // =====================================================
    // Controls Style
    // =====================================================

    setStyleSheet(
        "QLineEdit, QComboBox {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(71, 85, 105);"
        "border-radius: 8px;"
        "padding: 7px 9px;"
        "color: rgb(226, 232, 240);"
        "font-size: 12px;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        "border: 1px solid rgb(96, 165, 250);"
        "}"
        "QPushButton {"
        "background-color: rgb(30, 41, 59);"
        "border: 1px solid rgb(71, 85, 105);"
        "border-radius: 8px;"
        "padding: 7px 12px;"
        "color: rgb(226, 232, 240);"
        "font-size: 12px;"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(51, 65, 85);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(37, 99, 235);"
        "}"
        );


    // =====================================================
    // Result Table
    // =====================================================

    m_table =
        new QTableWidget;

    m_table->setColumnCount(
        7
        );

    m_table->setHorizontalHeaderLabels(
        {
            "Algorithm",
            "Input",
            "Output",
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

    m_table->setFocusPolicy(
        Qt::NoFocus
        );

    m_table->verticalHeader()
        ->setVisible(false);

    m_table->verticalHeader()
        ->setDefaultSectionSize(
            34
            );

    m_table->horizontalHeader()
        ->setMinimumHeight(
            34
            );

    m_table->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::ResizeToContents
            );

    m_table->horizontalHeader()
        ->setSectionResizeMode(
            1,
            QHeaderView::Stretch
            );

    m_table->horizontalHeader()
        ->setSectionResizeMode(
            2,
            QHeaderView::Stretch
            );

    m_table->setMinimumHeight(
        150
        );

    m_table->setMaximumHeight(
        165
        );

    m_table->setStyleSheet(
        "QTableWidget {"
        "background-color: rgb(17, 24, 39);"
        "border: 1px solid rgb(51, 65, 85);"
        "border-radius: 9px;"
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
        "font-size: 11px;"
        "font-weight: 600;"
        "}"
        );

    mainLayout->addWidget(
        m_table
        );


    // =====================================================
    // Status
    // =====================================================

    m_statusLabel =
        new QLabel(
            "Ready"
            );

    m_statusLabel->setStyleSheet(
        "color: rgb(148, 163, 184);"
        "font-size: 11px;"
        );

    mainLayout->addWidget(
        m_statusLabel
        );


    // =====================================================
    // Signals
    // =====================================================

    connect(
        m_sortButton,
        &QPushButton::clicked,
        this,
        &StudentPanel::sortData
        );

    connect(
        m_clearButton,
        &QPushButton::clicked,
        this,
        &StudentPanel::clearData
        );

    connect(
        m_inputEdit,
        &QLineEdit::returnPressed,
        this,
        &StudentPanel::sortData
        );
}


// =========================================================
// Parse Input
// =========================================================

std::vector<int> StudentPanel::parseInput() const
{
    std::vector<int> values;

    QString text =
        m_inputEdit->text();

    text.replace(
        ";",
        ","
        );

    const QStringList parts =
        text.split(
            ",",
            Qt::SkipEmptyParts
            );


    for (const QString &part : parts)
    {
        bool ok = false;

        const int value =
            part.trimmed().toInt(
                &ok
                );

        if (!ok)
        {
            return {};
        }

        values.push_back(
            value
            );
    }


    return values;
}


// =========================================================
// Sort
// =========================================================

void StudentPanel::sortData()
{
    const std::vector<int> input =
        parseInput();


    if (input.empty())
    {
        m_statusLabel->setText(
            "Invalid input. Example: 8, 3, 5, 1, 9"
            );

        return;
    }


    const QString algorithm =
        m_algorithmCombo->currentText();


    const StudentSortResult result =
        StudentSortRunner::run(
            input,
            algorithm
            );


    if (!result.completed)
    {
        m_statusLabel->setText(
            "Sorting failed."
            );

        return;
    }


    showResult(
        result.inputData,
        result.sortedData,
        result.algorithmName,
        result.comparisons,
        result.swaps,
        result.moves,
        result.executionTimeMs
        );


    m_statusLabel->setText(
        QString(
            "Sorting completed. Showing last %1 result(s)."
            )
            .arg(
                m_table->rowCount()
                )
        );
}


// =========================================================
// Show Result
// =========================================================

void StudentPanel::showResult(
    const std::vector<int> &input,
    const std::vector<int> &output,
    const QString &algorithm,
    std::size_t comparisons,
    std::size_t swaps,
    std::size_t moves,
    double timeMs
    )
{
    QStringList inputStrings;
    QStringList outputStrings;


    for (int value : input)
    {
        inputStrings.append(
            QString::number(
                value
                )
            );
    }


    for (int value : output)
    {
        outputStrings.append(
            QString::number(
                value
                )
            );
    }


    if (
        m_table->rowCount() >=
        MaxHistoryRows
        )
    {
        m_table->removeRow(
            0
            );
    }


    const int row =
        m_table->rowCount();


    m_table->insertRow(
        row
        );


    m_table->setItem(
        row,
        0,
        new QTableWidgetItem(
            algorithm
            )
        );


    m_table->setItem(
        row,
        1,
        new QTableWidgetItem(
            inputStrings.join(
                ", "
                )
            )
        );


    m_table->setItem(
        row,
        2,
        new QTableWidgetItem(
            outputStrings.join(
                ", "
                )
            )
        );


    m_table->setItem(
        row,
        3,
        new QTableWidgetItem(
            QString::number(
                static_cast<qulonglong>(
                    comparisons
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
                    swaps
                    )
                )
            )
        );


    m_table->setItem(
        row,
        5,
        new QTableWidgetItem(
            QString::number(
                static_cast<qulonglong>(
                    moves
                    )
                )
            )
        );


    m_table->setItem(
        row,
        6,
        new QTableWidgetItem(
            QString::number(
                timeMs,
                'f',
                4
                )
            )
        );
}


// =========================================================
// Clear
// =========================================================

void StudentPanel::clearData()
{
    m_inputEdit->clear();

    m_table->setRowCount(
        0
        );

    m_statusLabel->setText(
        "Ready"
        );
}
