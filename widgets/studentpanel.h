#ifndef STUDENTPANEL_H
#define STUDENTPANEL_H

#include <QWidget>
#include <vector>
class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;
class QTableWidget;

class StudentPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StudentPanel(QWidget *parent = nullptr);

private slots:
    void sortData();
    void clearData();

private:
    std::vector<int> parseInput() const;
    void showResult(
        const std::vector<int> &input,
        const std::vector<int> &output,
        const QString &algorithm,
        std::size_t comparisons,
        std::size_t swaps,
        std::size_t moves,
        double timeMs
        );

    QLineEdit *m_inputEdit;
    QComboBox *m_algorithmCombo;

    QPushButton *m_sortButton;
    QPushButton *m_clearButton;

    QTableWidget *m_table;

    QLabel *m_statusLabel;
};

#endif // STUDENTPANEL_H