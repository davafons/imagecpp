#pragma once

#include <QStatusBar>

namespace imagecpp {

// Forward declarations
class PixelInformationWidget;

/*
 *
 */
class MainStatusBar : public QStatusBar {
public:
  explicit MainStatusBar(QWidget *parent = nullptr);
  virtual ~MainStatusBar() = default;

  PixelInformationWidget *pixelInfoWidget() const { return pixel_info_widget_; }

private:
  PixelInformationWidget *pixel_info_widget_;
};

} // namespace imagecpp
