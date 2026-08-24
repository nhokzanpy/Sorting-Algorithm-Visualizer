#include "mainwindow.h"
#include "algorithms/bubblesort.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<int> testData = {8, 3, 6, 1, 5};

    SortingStatistics stats;

    const auto steps = BubbleSort::sort(testData, stats);

    if (!steps.empty())
    {
        const auto &result = steps.back().arrayState;

        QString resultText;

        for (int value : result)
        {
            resultText += QString::number(value) + " ";
        }

        qDebug() << "Bubble Sort result:" << resultText.trimmed();
        qDebug() << "Comparisons:" << stats.comparisons;
        qDebug() << "Swaps:" << stats.swaps;
        qDebug() << "Moves:" << stats.moves;
        qDebug() << "Time:" << stats.executionTimeMs << "ms";
    }

    MainWindow w;
    w.show();

    return a.exec();
}