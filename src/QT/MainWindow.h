//
// Created by soup on 04/01/2026.
//

#ifndef WEBCRAWLERCPP_MAINWINDOW_H
#define WEBCRAWLERCPP_MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLabel>
#include <QThread>
#include <QScrollBar>
#include <QVBoxLayout>

class CrawlerThread;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();
    void onStopClicked();
    void onCrawlerFinished();
    void appendLog(const QString &message);
    void updateProgress(int current, int total);

private:
    // UI Components
    QLineEdit *urlInput;
    QSpinBox *depthSpinBox;
    QSpinBox *linksSpinBox;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTextEdit *logTextEdit;
    QProgressBar *progressBar;
    QLabel *statusLabel;

    // Crawler thread
    CrawlerThread *crawlerThread;

    void setupUI();
    void createLayout();
};

class CrawlerThread : public QThread {
    Q_OBJECT

public:
    CrawlerThread(const QString &url, int depth, int links, QObject *parent = nullptr);
    void run() override;
    void stop();

    signals:
        void logMessage(const QString &message);
    void progressUpdate(int current, int total);
    void finished();

private:
    QString startUrl;
    int maxDepth;
    int maxLinks;
    bool shouldStop;
};

#endif
//WEBCRAWLERCPP_MAINWINDOW_H