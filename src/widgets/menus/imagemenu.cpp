#include "imagemenu.hpp"

#include <QFileDialog>

namespace imagecpp {

ImageMenu::ImageMenu(QWidget *parent) : QMenu(tr("Image"), parent) {

  // Duplicate
  duplicate_img_act_ = new QAction(tr("Duplicate image"), this);
  duplicate_img_act_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
  duplicate_img_act_->setStatusTip(
      tr("Duplicate current image and create a new window"));

  connect(duplicate_img_act_, &QAction::triggered, this, &ImageMenu::duplicateImage);

  show_histogram_act_ = new QAction(tr("Show histogram"), this);
  show_histogram_act_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
  duplicate_img_act_->setStatusTip(tr("Open the histogram related to the image"));

  connect(show_histogram_act_, &QAction::triggered, this, &ImageMenu::showHistogram);

  // Grayscale
  grayscale_act_ = new QAction(tr("To grayscale..."), this);
  grayscale_act_->setStatusTip(tr("Convert image to grayscale"));

  connect(grayscale_act_, &QAction::triggered, this, &ImageMenu::grayscale);

  // Inverse
  inverse_act_ = new QAction(tr("Inverse"), this);
  inverse_act_->setStatusTip(tr("Transform the image to its inverse (negative)"));

  connect(inverse_act_, &QAction::triggered, this, &ImageMenu::inverse);

  // Linear Transform
  linear_trans_act_ = new QAction(tr("Linear transform..."), this);
  linear_trans_act_->setStatusTip(
      tr("Perform a linear transformation (specifying the in/out values)"));

  connect(linear_trans_act_, &QAction::triggered, this, &ImageMenu::linearTransform);

  // Brightness and Contrast
  bac_act_ = new QAction(tr("Brightnes/Constrast..."), this);
  bac_act_->setStatusTip(tr("Change Brightnes and Contrast properties of the image"));

  connect(bac_act_, &QAction::triggered, this, &ImageMenu::brightnessAndConstrast);

  // Gamma correction
  gamma_corr_act_ = new QAction(tr("Gamma correction..."), this);
  gamma_corr_act_->setStatusTip(tr("Gamma correction"));

  connect(gamma_corr_act_, &QAction::triggered, this, &ImageMenu::gammaCorrection);

  // Image difference
  image_difference_act_ = new QAction(tr("Image difference..."), this);
  image_difference_act_->setStatusTip(tr("Image difference between two images."));

  connect(
      image_difference_act_, &QAction::triggered, this, &ImageMenu::imageDifference);

  // Digitalization
  digitalization_act_ = new QAction(tr("Digitalization..."), this);
  digitalization_act_->setStatusTip(tr("Digitalization and sampling of the image"));

  connect(digitalization_act_, &QAction::triggered, this, &ImageMenu::digitalization);

  // Equalization
  equalization_act_ = new QAction(tr("Equalization"), this);
  equalization_act_->setStatusTip(tr("Equalize image"));

  connect(equalization_act_, &QAction::triggered, this, &ImageMenu::equalization);

  // Specification
  specification_act_ = new QAction(tr("Specification"), this);
  specification_act_->setStatusTip(tr("Image specification"));

  connect(specification_act_, &QAction::triggered, this, &ImageMenu::specification);

  // Profile
  profile_act_ = new QAction(tr("Profile"), this);
  profile_act_->setStatusTip(tr("Profile"));

  connect(profile_act_, &QAction::triggered, this, &ImageMenu::profile);

  // Transform groups
  hmirror_act_ = new QAction(tr("Horizontal mirror"), this);
  hmirror_act_->setStatusTip(tr("Mirror image horizontally"));

  connect(hmirror_act_, &QAction::triggered, this, &ImageMenu::horizontalMirror);

  vmirror_act_ = new QAction(tr("Vertical mirror"), this);
  vmirror_act_->setStatusTip(tr("Mirror image vertically"));

  connect(vmirror_act_, &QAction::triggered, this, &ImageMenu::verticalMirror);

  transform_menu_ = new QMenu(tr("Transform..."), this);
  transform_menu_->addAction(hmirror_act_);
  transform_menu_->addAction(vmirror_act_);

  // Menu layout

  addAction(duplicate_img_act_);
  addAction(show_histogram_act_);

  addSeparator();

  addAction(grayscale_act_);
  addAction(inverse_act_);
  addAction(linear_trans_act_);
  addAction(bac_act_);
  addAction(gamma_corr_act_);
  addAction(image_difference_act_);
  addAction(digitalization_act_);
  addAction(equalization_act_);
  addAction(specification_act_);
  addAction(profile_act_);

  addMenu(transform_menu_);
}

}  // namespace imagecpp
