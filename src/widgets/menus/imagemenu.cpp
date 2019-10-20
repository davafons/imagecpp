#include "imagemenu.hpp"

#include <QFileDialog>

namespace imagecpp {

ImageMenu::ImageMenu(QWidget *parent) : QMenu(tr("Image"), parent) {

  // Duplicate
  duplicate_img_act_ = new QAction(tr("Duplicate image"), this);
  duplicate_img_act_->setShortcut(
      QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D));
  duplicate_img_act_->setStatusTip(
      tr("Duplicate current image and create a new window"));

  connect(duplicate_img_act_, &QAction::triggered, this,
          &ImageMenu::duplicateImage);

  // Grayscale
  grayscale_act_ = new QAction(tr("To grayscale..."), this);
  grayscale_act_->setStatusTip(tr("Convert image to grayscale"));

  connect(grayscale_act_, &QAction::triggered, this, &ImageMenu::grayscale);

  // Inverse
  inverse_act_ = new QAction(tr("Inverse"), this);
  inverse_act_->setStatusTip(
      tr("Transform the image to its inverse (negative)"));

  connect(inverse_act_, &QAction::triggered, this, &ImageMenu::inverse);

  // Linear Transform
  linear_trans_act_ = new QAction(tr("Linear transform..."), this);
  linear_trans_act_->setStatusTip(
      tr("Perform a linear transformation (specifying the in/out values)"));

  connect(linear_trans_act_, &QAction::triggered, this,
          &ImageMenu::linearTransform);

  // Brightness and Contrast
  bac_act_ = new QAction(tr("Brightnes/Constrast..."), this);
  bac_act_->setStatusTip(
      tr("Change Brightnes and Contrast properties of the image"));

  connect(bac_act_, &QAction::triggered, this,
          &ImageMenu::brightnessAndConstrast);

  // Menu layout

  addAction(duplicate_img_act_);
  addSeparator();
  addAction(grayscale_act_);
  addAction(inverse_act_);
  addAction(linear_trans_act_);
  addAction(bac_act_);
}

} // namespace imagecpp
