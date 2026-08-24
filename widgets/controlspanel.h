#ifndef CONTROLSPANEL_H
#define CONTROLSPANEL_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class QPushButton;
class QSlider;

class ControlsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlsPanel(QWidget *parent = nullptr);

    QString inputText() const;
    QString selectedAlgorithm() const;

    int speedValue() const;

    void setInputText(const QString &text);

signals:
    void randomRequested();
    void playRequested();
    void pauseRequested();
    void nextRequested();
    void resetRequested();

private:
    QLineEdit *m_inputEdit;
    QComboBox *m_algorithmCombo;

    QPushButton *m_randomButton;
    QPushButton *m_playButton;
    QPushButton *m_pauseButton;
    QPushButton *m_nextButton;
    QPushButton *m_resetButton;

    QSlider *m_speedSlider;
};

#endif // CONTROLSPANEL_H