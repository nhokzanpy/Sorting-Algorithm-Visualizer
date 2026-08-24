#include "statisticspanel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>


StatisticsPanel::StatisticsPanel(QWidget *parent)
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

    mainLayout->setSpacing(12);


    auto *statsLayout =
        new QHBoxLayout;

    statsLayout->setSpacing(12);


    m_comparisonsLabel =
        new QLabel(
            "Comparisons: 0"
            );

    m_swapsLabel =
        new QLabel(
            "Swaps: 0 | Moves: 0"
            );

    m_timeLabel =
        new QLabel(
            "Time: 0.0000 ms"
            );


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


    statsLayout->addWidget(
        m_comparisonsLabel
        );

    statsLayout->addWidget(
        m_swapsLabel
        );

    statsLayout->addWidget(
        m_timeLabel
        );


    mainLayout->addLayout(
        statsLayout
        );


    m_statusLabel =
        new QLabel(
            "Ready"
            );

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


    mainLayout->addWidget(
        m_statusLabel
        );
}


void StatisticsPanel::reset()
{
    m_swaps = 0;
    m_moves = 0;

    setComparisons(0);
    setSwaps(0);
    setMoves(0);
    setTime(0.0);
    setStatus("Ready");
}


void StatisticsPanel::setComparisons(
    std::size_t value
    )
{
    m_comparisonsLabel->setText(
        "Comparisons: " +
        QString::number(
            static_cast<qulonglong>(
                value
                )
            )
        );
}


void StatisticsPanel::setSwaps(
    std::size_t value
    )
{
    m_swaps = value;

    m_swapsLabel->setText(
        "Swaps: " +
        QString::number(
            static_cast<qulonglong>(
                m_swaps
                )
            ) +
        " | Moves: " +
        QString::number(
            static_cast<qulonglong>(
                m_moves
                )
            )
        );
}


void StatisticsPanel::setMoves(
    std::size_t value
    )
{
    m_moves = value;

    m_swapsLabel->setText(
        "Swaps: " +
        QString::number(
            static_cast<qulonglong>(
                m_swaps
                )
            ) +
        " | Moves: " +
        QString::number(
            static_cast<qulonglong>(
                m_moves
                )
            )
        );
}


void StatisticsPanel::setTime(
    double milliseconds
    )
{
    m_timeLabel->setText(
        "Time: " +
        QString::number(
            milliseconds,
            'f',
            4
            ) +
        " ms"
        );
}


void StatisticsPanel::setStatus(
    const QString &text
    )
{
    m_statusLabel->setText(
        text
        );
}