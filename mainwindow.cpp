#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pages/visualizerpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet(R"(
    QMainWindow {
        background-color: rgb(15, 23, 42);
    }

    QWidget {
        background-color: rgb(15, 23, 42);
        color: rgb(226, 232, 240);
        font-family: "Segoe UI";
        font-size: 14px;
    }

    QLabel {
        background-color: transparent;
        color: rgb(226, 232, 240);
    }

    QLineEdit,
    QComboBox {
        background-color: rgb(30, 41, 59);
        color: rgb(241, 245, 249);

        border: 1px solid rgb(71, 85, 105);
        border-radius: 7px;

        padding: 8px 10px;
    }

    QLineEdit:focus,
    QComboBox:focus {
        border: 1px solid rgb(59, 130, 246);
    }

    QPushButton {
        background-color: rgb(30, 41, 59);
        color: rgb(226, 232, 240);

        border: 1px solid rgb(71, 85, 105);
        border-radius: 7px;

        padding: 8px 14px;
    }

    QPushButton:hover {
        background-color: rgb(51, 65, 85);
        border-color: rgb(100, 116, 139);
    }

    QPushButton:pressed {
        background-color: rgb(71, 85, 105);
    }

    QComboBox::drop-down {
        border: none;
        width: 24px;
    }

    QSlider::groove:horizontal {
        height: 5px;
        background-color: rgb(51, 65, 85);
        border-radius: 2px;
    }

    QSlider::sub-page:horizontal {
        background-color: rgb(59, 130, 246);
        border-radius: 2px;
    }

    QSlider::handle:horizontal {
        background-color: rgb(96, 165, 250);

        width: 16px;
        height: 16px;

        margin: -6px 0;

        border-radius: 8px;
    }
)");

    auto *visualizerPage =
        new VisualizerPage(this);

    setCentralWidget(
        visualizerPage
        );

    resize(
        1200,
        760
        );

    setWindowTitle(
        "Sorting Algorithm Visualizer"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}