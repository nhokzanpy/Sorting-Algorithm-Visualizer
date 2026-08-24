#ifndef STATISTICSPANEL_H
#define STATISTICSPANEL_H

#include <QWidget>

class QLabel;

class StatisticsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsPanel(QWidget *parent = nullptr);

    void reset();

    void setComparisons(std::size_t value);
    void setSwaps(std::size_t value);
    void setMoves(std::size_t value);
    void setTime(double milliseconds);
    void setStatus(const QString &text);

private:
    QLabel *m_comparisonsLabel;
    QLabel *m_swapsLabel;
    QLabel *m_timeLabel;
    QLabel *m_statusLabel;

    std::size_t m_swaps = 0;
    std::size_t m_moves = 0;
};

#endif // STATISTICSPANEL_H