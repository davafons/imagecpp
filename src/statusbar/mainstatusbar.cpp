#include "mainstatusbar.hpp"

MainStatusBar::MainStatusBar(QWidget *parent)
    : pixel_info_widget_(new PixelInformationWidget()), QStatusBar(parent) {
  addWidget(pixel_info_widget_);
}
