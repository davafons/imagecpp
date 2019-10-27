#pragma once

#include <QMenu>

namespace imagecpp {

/*
 */
class ImageMenu : public QMenu {
  Q_OBJECT
public:
  explicit ImageMenu(QWidget *parent = nullptr);
  virtual ~ImageMenu() = default;

signals:
  void duplicateImage();
  void showHistogram();

  void grayscale();
  void inverse();
  void linearTransform();
  void brightnessAndConstrast();
  void gammaCorrection();

private:
  QAction *duplicate_img_act_;
  QAction *show_histogram_act_;

  QAction *grayscale_act_;
  QAction *inverse_act_;
  QAction *linear_trans_act_;
  QAction *bac_act_;
  QAction *gamma_corr_act_;
};

} // namespace imagecpp
