#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QImage>
#include <QLabel>

#include <QMdiArea>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());

private:
  void createActions();
  void createMenus();

private slots:
  void openImage();

private:
  QMenu *file_menu_;
  QMenu *options_menu_;

  QAction *quit_act_;
  QAction *open_act_;

  QAction *toggle_subtabs_act_;

  QMdiArea *mdi_area_;
};
