#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  imagecpp::MainWindow main_window;

  main_window.show();

  return app.exec();
}
