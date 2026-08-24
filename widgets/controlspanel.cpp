#include "controlspanel.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>


ControlsPanel::ControlsPanel(QWidget *parent)
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


    // =====================================================
    // Input Data
    // =====================================================

    auto *inputLabel =
        new QLabel("Input Data");

    inputLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(
        inputLabel
        );


    auto *inputLayout =
        new QHBoxLayout;

    inputLayout->setSpacing(10);


    m_inputEdit =
        new QLineEdit;

    m_randomButton =
        new QPushButton("Random");


    inputLayout->addWidget(
        m_inputEdit
        );

    inputLayout->addWidget(
        m_randomButton
        );


    mainLayout->addLayout(
        inputLayout
        );


    // =====================================================
    // Algorithm + Playback
    // =====================================================

    auto *algorithmLabel =
        new QLabel("Algorithm");

    algorithmLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(
        algorithmLabel
        );


    auto *controlsLayout =
        new QHBoxLayout;

    controlsLayout->setSpacing(10);


    m_algorithmCombo =
        new QComboBox;

    m_algorithmCombo->addItem(
        "Bubble Sort"
        );

    m_algorithmCombo->addItem(
        "Selection Sort"
        );

    m_algorithmCombo->addItem(
        "Insertion Sort"
        );

    m_algorithmCombo->addItem(
        "Merge Sort"
        );
    m_playButton =
        new QPushButton("Play");

    m_pauseButton =
        new QPushButton("Pause");

    m_nextButton =
        new QPushButton("Next");

    m_resetButton =
        new QPushButton("Reset");


    m_playButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(37, 99, 235);"
        "border: 1px solid rgb(59, 130, 246);"
        "color: white;"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(59, 130, 246);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(29, 78, 216);"
        "}"
        );


    m_resetButton->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(194, 65, 12);"
        "border: 1px solid rgb(234, 88, 12);"
        "color: white;"
        "font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "background-color: rgb(234, 88, 12);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(154, 52, 18);"
        "}"
        );


    controlsLayout->addWidget(
        m_algorithmCombo
        );

    controlsLayout->addWidget(
        m_playButton
        );

    controlsLayout->addWidget(
        m_pauseButton
        );

    controlsLayout->addWidget(
        m_nextButton
        );

    controlsLayout->addWidget(
        m_resetButton
        );


    mainLayout->addLayout(
        controlsLayout
        );


    // =====================================================
    // Speed
    // =====================================================

    auto *speedLabel =
        new QLabel("Speed");

    speedLabel->setStyleSheet(
        "color: rgb(203, 213, 225);"
        "font-size: 13px;"
        "font-weight: 600;"
        );

    mainLayout->addWidget(
        speedLabel
        );


    auto *speedLayout =
        new QHBoxLayout;

    speedLayout->setSpacing(8);


    speedLayout->addWidget(
        new QLabel("Slow")
        );


    m_speedSlider =
        new QSlider(
            Qt::Horizontal
            );

    m_speedSlider->setRange(
        50,
        800
        );

    m_speedSlider->setValue(
        300
        );


    speedLayout->addWidget(
        m_speedSlider
        );

    speedLayout->addWidget(
        new QLabel("Fast")
        );


    mainLayout->addLayout(
        speedLayout
        );


    // =====================================================
    // Signals
    // =====================================================

    connect(
        m_randomButton,
        &QPushButton::clicked,
        this,
        &ControlsPanel::randomRequested
        );

    connect(
        m_playButton,
        &QPushButton::clicked,
        this,
        &ControlsPanel::playRequested
        );

    connect(
        m_pauseButton,
        &QPushButton::clicked,
        this,
        &ControlsPanel::pauseRequested
        );

    connect(
        m_nextButton,
        &QPushButton::clicked,
        this,
        &ControlsPanel::nextRequested
        );

    connect(
        m_resetButton,
        &QPushButton::clicked,
        this,
        &ControlsPanel::resetRequested
        );
}


QString ControlsPanel::inputText() const
{
    return m_inputEdit->text();
}


QString ControlsPanel::selectedAlgorithm() const
{
    return m_algorithmCombo->currentText();
}


int ControlsPanel::speedValue() const
{
    return m_speedSlider->value();
}


void ControlsPanel::setInputText(
    const QString &text
    )
{
    m_inputEdit->setText(
        text
        );
}