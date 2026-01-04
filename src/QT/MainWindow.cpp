//
// Created by soup on 04/01/2026.
//

#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include "../interfaces/WebCrawler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), crawlerThread(nullptr) {
    setupUI();
    createLayout();

    setWindowTitle("WebCrawler GUI");
    resize(800, 600);
}

MainWindow::~MainWindow() {
    if (crawlerThread && crawlerThread->isRunning()) {
        crawlerThread->stop();
        crawlerThread->wait();
    }
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Input URL
    urlInput = new QLineEdit("https://example.com");
    urlInput->setPlaceholderText("Enter URL to crawl...");

    // Depth spinner
    depthSpinBox = new QSpinBox();
    depthSpinBox->setRange(1, 5);
    depthSpinBox->setValue(2);
    depthSpinBox->setPrefix("Depth: ");

    // Links per page spinner
    linksSpinBox = new QSpinBox();
    linksSpinBox->setRange(1, 100);
    linksSpinBox->setValue(50);
    linksSpinBox->setPrefix("Links/Page: ");

    // Buttons
    startButton = new QPushButton("Start Crawling");
    stopButton = new QPushButton("Stop");
    stopButton->setEnabled(false);

    // Log text area
    logTextEdit = new QTextEdit();
    logTextEdit->setReadOnly(true);
    logTextEdit->setStyleSheet("QTextEdit { background-color: #1e1e1e; color: #00ff00; font-family: Consolas; }");

    // Progress bar
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    // Status label
    statusLabel = new QLabel("Ready");

    // Connect signals
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::onStopClicked);
}

void MainWindow::createLayout() {
    QWidget* central = this->centralWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QGroupBox* inputGroup = new QGroupBox("Configuration");
    QVBoxLayout* inputLayout = new QVBoxLayout();

    inputLayout->addWidget(new QLabel("URL:"));
    inputLayout->addWidget(urlInput);

    QHBoxLayout* spinnerLayout = new QHBoxLayout();
    spinnerLayout->addWidget(depthSpinBox);
    spinnerLayout->addWidget(linksSpinBox);
    inputLayout->addLayout(spinnerLayout);

    inputGroup->setLayout(inputLayout);
    mainLayout->addWidget(inputGroup);

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    mainLayout->addLayout(buttonLayout);

    // Log section
    QGroupBox* logGroup = new QGroupBox("Crawling Log");
    QVBoxLayout* logLayout = new QVBoxLayout();
    logLayout->addWidget(logTextEdit);
    logGroup->setLayout(logLayout);
    mainLayout->addWidget(logGroup);

    // Progress section
    mainLayout->addWidget(progressBar);
    mainLayout->addWidget(statusLabel);

    central->setLayout(mainLayout);
}

void MainWindow::onStartClicked() {
    QString url = urlInput->text().trimmed();

    if (url.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a URL");
        return;
    }

    // Clear log
    logTextEdit->clear();
    progressBar->setValue(0);

    // Disable start, enable stop
    startButton->setEnabled(false);
    stopButton->setEnabled(true);
    statusLabel->setText("Crawling...");

    // Create and start crawler thread
    crawlerThread = new CrawlerThread(
        url,
        depthSpinBox->value(),
        linksSpinBox->value(),
        this
    );

    connect(crawlerThread, &CrawlerThread::logMessage, this, &MainWindow::appendLog);
    connect(crawlerThread, &CrawlerThread::progressUpdate, this, &MainWindow::updateProgress);
    connect(crawlerThread, &CrawlerThread::finished, this, &MainWindow::onCrawlerFinished);

    crawlerThread->start();
}

void MainWindow::onStopClicked() {
    if (crawlerThread && crawlerThread->isRunning()) {
        appendLog("Stopping crawler...");
        crawlerThread->stop();
        crawlerThread->wait();
    }
}

void MainWindow::onCrawlerFinished() {
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    statusLabel->setText("Finished");
    appendLog("=== CRAWLING COMPLETED ===");
    progressBar->setValue(100);
}

void MainWindow::appendLog(const QString& message) {
    logTextEdit->append(message);
    // Auto-scroll to bottom
    logTextEdit->verticalScrollBar()->setValue(
        logTextEdit->verticalScrollBar()->maximum()
    );
}

void MainWindow::updateProgress(int current, int total) {
    if (total > 0) {
        int percentage = (current * 100) / total;
        progressBar->setValue(percentage);
        statusLabel->setText(QString("Pages: %1 / %2").arg(current).arg(total));
    }
}


CrawlerThread::CrawlerThread(const QString& url, int depth, int links, QObject* parent)
    : QThread(parent), startUrl(url), maxDepth(depth), maxLinks(links), shouldStop(false) {
}

void CrawlerThread::run() {
    emit logMessage("=== START CRAWLING ===");
    emit logMessage("URL: " + startUrl);
    emit logMessage("Max Depth: " + QString::number(maxDepth));
    emit logMessage("Max Links: " + QString::number(maxLinks));
    emit logMessage("");

    WebCrawler crawler(maxDepth, maxLinks);
    crawler.crawl(startUrl.toStdString());

    // TODO
    // for (int i = 0; i < 10 && !shouldStop; i++) {
    //     emit logMessage(QString("[Depth 0] Crawling page %1...").arg(i + 1));
    //     emit progressUpdate(i + 1, 10);
    //     QThread::msleep(500);
    // }

    emit finished();
}

void CrawlerThread::stop() {
    shouldStop = true;
}