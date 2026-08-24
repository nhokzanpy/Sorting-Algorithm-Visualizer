#include "sortingvisualizer.h"

#include <QPainter>
#include <QPaintEvent>
#include <algorithm>

SortingVisualizer::SortingVisualizer(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(320);
}

void SortingVisualizer::setData(const std::vector<int> &data)
{
    m_data = data;

    m_firstIndex = -1;
    m_secondIndex = -1;
    m_stepType = SortingStepType::Complete;

    m_sortedIndices.clear();

    update();
}

void SortingVisualizer::showStep(const SortingStep &step)
{
    m_data = step.arrayState;

    m_firstIndex = step.firstIndex;
    m_secondIndex = step.secondIndex;
    m_stepType = step.type;

    if (step.type == SortingStepType::MarkSorted &&
        step.firstIndex >= 0)
    {
        m_sortedIndices.insert(step.firstIndex);
    }
    if (step.type == SortingStepType::Complete)
    {
        m_sortedIndices.clear();

        for (int i = 0;
             i < static_cast<int>(m_data.size());
             ++i)
        {
            m_sortedIndices.insert(i);
        }
    }
    update();
}

void SortingVisualizer::resetVisualization()
{
    m_firstIndex = -1;
    m_secondIndex = -1;
    m_stepType = SortingStepType::Complete;

    update();
}

void SortingVisualizer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background
    painter.fillRect(
        rect(),
        QColor(17, 24, 39)
        );

    // Không có dữ liệu
    if (m_data.empty())
    {
        painter.setPen(
            QColor(148, 163, 184)
            );

        painter.drawText(
            rect(),
            Qt::AlignCenter,
            "No data"
            );

        return;
    }

    const int margin = 30;

    const int availableWidth =
        width() - margin * 2;

    const int availableHeight =
        height() - margin * 2;

    const int count =
        static_cast<int>(
            m_data.size()
            );

    const int maxValue =
        *std::max_element(
            m_data.begin(),
            m_data.end()
            );

    if (maxValue <= 0)
    {
        return;
    }

    const double slotWidth =
        static_cast<double>(
            availableWidth
            ) / count;

    const double barWidth =
        slotWidth * 0.65;

    for (int i = 0; i < count; ++i)
    {
        const double ratio =
            static_cast<double>(
                m_data[i]
                ) / maxValue;

        const double barHeight =
            availableHeight *
            ratio *
            0.85;

        const double x =
            margin +
            i * slotWidth +
            (slotWidth - barWidth) / 2.0;

        const double y =
            height() -
            margin -
            barHeight;

        // Normal bar
        QColor color(
            100,
            116,
            139
            );

        if (m_sortedIndices.find(i) != m_sortedIndices.end())
        {
            color = QColor(
                34,
                197,
                94
                );
        }

        // Highlight current indices
        if (i == m_firstIndex ||
            i == m_secondIndex)
        {
            if (m_stepType ==
                SortingStepType::Compare)
            {
                // Amber
                color = QColor(
                    245,
                    158,
                    11
                    );
            }
            else if (m_stepType ==
                     SortingStepType::Swap)
            {
                // Red
                color = QColor(
                    239,
                    68,
                    68
                    );
            }
            else if (m_stepType ==
                     SortingStepType::MarkSorted)
            {
                // Green
                color = QColor(
                    34,
                    197,
                    94
                    );
            }
        }

        painter.setPen(
            Qt::NoPen
            );

        painter.setBrush(
            color
            );

        QRectF barRect(
            x,
            y,
            barWidth,
            barHeight
            );

        painter.drawRoundedRect(
            barRect,
            4,
            4
            );

        // Value above bar
        painter.setPen(
            QColor(
                248,
                250,
                252
                )
            );

        painter.drawText(
            QRectF(
                x,
                y - 25,
                barWidth,
                20
                ),
            Qt::AlignCenter,
            QString::number(
                m_data[i]
                )
            );

        // Index below bar
        painter.setPen(
            QColor(
                148,
                163,
                184
                )
            );

        painter.drawText(
            QRectF(
                x,
                height() - margin + 5,
                barWidth,
                20
                ),
            Qt::AlignCenter,
            "[" +
                QString::number(i) +
                "]"
            );
    }
}