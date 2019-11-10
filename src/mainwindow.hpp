#pragma once

#include <QMainWindow>

#include "image/histogramview.hpp"
#include "manager/documentsmanager.hpp"
#include "widgets/menus/mainmenubar.hpp"
#include "widgets/statusbar/mainstatusbar.hpp"

// Forward declarations
class QUndoView;
class QUndoGroup;

namespace imagecpp {

// Forward declarations
class SubWindowsArea;

/*
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
  virtual ~MainWindow();

private slots:
  void updateViews(Document *document);  // TODO: Pass const

private:
  void createMenuBar();
  void createStatusBar();
  void createSubWindowsArea();
  void createDocks();

  void showHistogram();

  template <class Operation, typename... Args>
  void executeOperation(Document *document, Args &&... args);

private:
  MainMenuBar main_menu_bar_;
  MainStatusBar main_status_bar_;

  DocumentsManager documents_manager_;

  SubWindowsArea *mdi_area_;
  QUndoGroup *undo_group_;
  QUndoView *undo_view_;

  HistogramView *hist_view_;
};

}  // namespace imagecpp
