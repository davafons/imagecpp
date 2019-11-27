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
  void imageDifference();
  void imageChange();
  void digitalization();
  void equalization();
  void specification();
  void filter();
  void profile();

  void horizontalMirror();
  void verticalMirror();
  void transpose();
  void rotation();

private:
  QAction *duplicate_img_act_;
  QAction *show_histogram_act_;

  QAction *grayscale_act_;
  QAction *inverse_act_;
  QAction *linear_trans_act_;
  QAction *bac_act_;
  QAction *gamma_corr_act_;
  QAction *image_difference_act_;
  QAction *image_change_act_;
  QAction *digitalization_act_;
  QAction *equalization_act_;
  QAction *specification_act_;
  QAction *filter_act_;
  QAction *profile_act_;

  QMenu *transform_menu_;
  QAction *hmirror_act_;
  QAction *vmirror_act_;
  QAction *transpose_act_;
  QAction *rotation_act_;
};

}  // namespace imagecpp
