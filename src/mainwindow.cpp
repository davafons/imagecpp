#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QMenuBar>
#include <QSizeGrip>
#include <QSizePolicy>
#include <QUndoGroup>
#include <QUndoView>

#include "image/document.hpp"
#include "operations/grayscale.hpp"
#include "operations/private/operationconfigdialog.hpp"
#include "widgets/dock/resizabledockwidget.hpp"
#include "widgets/image/imagedisplayarea.hpp"
#include "widgets/image/imagesubwindow.hpp"
#include "widgets/image/subwindowsarea.hpp"
#include "widgets/statusbar/pixelinformationwidget.hpp"

namespace imagecpp {

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), mdi_area_(new SubWindowsArea()),
      undo_group_(new QUndoGroup()), undo_view_(new QUndoView()),
      hist_view_(new HistogramView()) {

  // MenuBar and StatusBar
  createMenuBar();
  createStatusBar();

  // UndoView
  undo_view_->setGroup(undo_group_);

  // MdiArea
  createSubWindowsArea();

  // Docks
  createDocks();

  // DocumentsManager

  // Add new window when opening a document
  connect(&documents_manager_, &DocumentsManager::newDocumentOpened, mdi_area_,
          &SubWindowsArea::addDocumentWindow);

  connect(&documents_manager_, &DocumentsManager::newDocumentOpened, this,
          [this](Document *document) {
            if (document) {
              undo_group_->addStack(document->undoStack());

              connect(document, &Document::histogramChanged, hist_view_,
                      &HistogramView::setHistogram);
            }
          });

  connect(&documents_manager_, &DocumentsManager::documentSaved, this,
          [this](Document *, const QString &file_path) {
            main_status_bar_.showSavedFilePathMessage(file_path);
          });
}

MainWindow::~MainWindow() {
  delete mdi_area_;
  delete undo_group_;
  delete undo_view_;
}

void MainWindow::createMenuBar() {
  setMenuBar(&main_menu_bar_);

  main_menu_bar_.createUndoActions(undo_group_);

  connect(&main_menu_bar_, &MainMenuBar::open, &documents_manager_,
          &DocumentsManager::open);

  connect(&main_menu_bar_, &MainMenuBar::save, &documents_manager_,
          [this] { documents_manager_.save(mdi_area_->activeDocument()); });

  connect(&main_menu_bar_, &MainMenuBar::saveAs, &documents_manager_,
          [this] { documents_manager_.saveAs(mdi_area_->activeDocument()); });

  // TODO: Add "Save copy connection"

  connect(&main_menu_bar_, &MainMenuBar::closeView, mdi_area_,
          &SubWindowsArea::closeActiveSubWindow);
  connect(&main_menu_bar_, &MainMenuBar::closeAll, mdi_area_,
          &SubWindowsArea::closeAllSubWindows);
  connect(&main_menu_bar_, &MainMenuBar::quit, qApp, &QApplication::quit);

  connect(&main_menu_bar_, &MainMenuBar::undo, undo_group_, &QUndoGroup::undo);
  connect(&main_menu_bar_, &MainMenuBar::redo, undo_group_, &QUndoGroup::redo);

  connect(
      &main_menu_bar_, &MainMenuBar::duplicateImage, &documents_manager_,
      [this] { documents_manager_.duplicate(mdi_area_->activeDocument()); });

  // Operations

  connect(
      &main_menu_bar_, &MainMenuBar::toGrayscale, &documents_manager_, [this] {
        executeOperation<GrayscaleConfigDialog>(mdi_area_->activeDocument());
      });

  connect(&main_menu_bar_, &MainMenuBar::toggleTabsView, mdi_area_,
          &SubWindowsArea::toggleTabsView);
  connect(&main_menu_bar_, &MainMenuBar::toggleHistoryWindow, undo_view_,
          &SubWindowsArea::setVisible);
}

void MainWindow::createStatusBar() { setStatusBar(&main_status_bar_); }

void MainWindow::createSubWindowsArea() {
  setCentralWidget(mdi_area_);

  connect(mdi_area_, &SubWindowsArea::subwindowAdded, this,
          [this](ImageSubWindow *w) {
            connect(w, &ImageSubWindow::pixelInformation,
                    main_status_bar_.pixelInfoWidget(),
                    &PixelInformationWidget::onPixelInformationReceived);
          });

  connect(mdi_area_, &SubWindowsArea::activeDocumentChanged, this,
          &MainWindow::updateViews);
}

void MainWindow::createDocks() {
  // Histogram view
  ResizableDockWidget *histogram_dock =
      new ResizableDockWidget(tr("Histogram"), this);
  histogram_dock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                  Qt::RightDockWidgetArea);
  histogram_dock->setWidget(hist_view_);
  addDockWidget(Qt::RightDockWidgetArea, histogram_dock);

  // History view
  ResizableDockWidget *history_dock =
      new ResizableDockWidget(tr("History"), this);
  history_dock->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
  history_dock->setWidget(undo_view_);
  addDockWidget(Qt::RightDockWidgetArea, history_dock);
}

void MainWindow::updateViews(Document *document) {
  // TODO: Set null if nullptr passed? (To reset interface)
  if (document) {
    undo_group_->setActiveStack(document->undoStack());
    hist_view_->setHistogram(document->histogram());
  }
}

template <class Operation>
void MainWindow::executeOperation(Document *document) {
  if (document == nullptr) {
    return;
  }

  Operation op(document);
  int return_value = op.exec();

  if (return_value) {
    document->undoStack()->push(op.command());
  }

  // TODO: Signal?
  updateViews(document);
};

} // namespace imagecpp
