#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QString>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags) {

  createActions();
  createMenus();

  setStatusBar(statusBar());
}

void MainWindow::createActions() {
  quitAct = new QAction(tr("&Quit"), this);
  quitAct->setShortcut(QKeySequence::Quit);
  quitAct->setStatusTip(tr("Quit from the application"));

  connect(quitAct, &QAction::triggered, qApp, &QApplication::quit);

  openAct = new QAction(tr("&Open"), this);
  openAct->setShortcut(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an image"));

  connect(openAct, &QAction::triggered, this, &MainWindow::openImage);
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAct);
}

void MainWindow::openImage() {
  qDebug() << "openImage() called";
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "~", tr("Image Files(*.png *.jpg *.bmp)"));

  if(!fileName.isEmpty()) {
    qDebug() << "Opening image: " << fileName;
  }
}
