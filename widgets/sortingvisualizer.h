#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QWidget>
#include <vector>

#include "../models/sortingstep.h"
#include <set>

class SortingVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit SortingVisualizer(QWidget *parent = nullptr);

    void setData(const std::vector<int> &data);
    void showStep(const SortingStep &step);
    void resetVisualization();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<int> m_data;

    int m_firstIndex = -1;
    int m_secondIndex = -1;

    SortingStepType m_stepType = SortingStepType::Complete;

    std::set<int> m_sortedIndices;
};

#endif // SORTINGVISUALIZER_H