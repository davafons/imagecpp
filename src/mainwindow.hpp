#include <QAction>
#include <QMainWindow>
#include <QMenu>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr,
             Qt::WindowFlags flags = Qt::WindowFlags());

private:
  void createActions();
  void createMenus();

public slots:
  void openImage();

private:
  QMenu *fileMenu;

  QAction *quitAct;
  QAction *openAct;
};
