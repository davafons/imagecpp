#include "mainstatusbar.hpp"

#include "pixelinformationwidget.hpp"

namespace imagecpp {

MainStatusBar::MainStatusBar(QWidget *parent)
    : pixel_info_widget_(new PixelInformationWidget()), QStatusBar(parent) {
  addWidget(pixel_info_widget_);
}

void MainStatusBar::showSavedFilePathMessage(const QString &file_path) {
  const int SHOW_TIME = 2000;

  showMessage(QString("Image saved on %1").arg(file_path), SHOW_TIME);
}

} // namespace imagecpp
