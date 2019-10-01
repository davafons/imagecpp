#include "imagemenu.hpp"

#include <QFileDialog>

ImageMenu::ImageMenu(QWidget *parent) : QMenu(tr("Image"), parent) {

  duplicate_img_act_ = new QAction(tr("Duplicate image"), this);
  duplicate_img_act_->setStatusTip(
      tr("Duplicate current image and create a new window"));

  to_grayscale_act_ = new QAction(tr("To grayscale"), this);
  to_grayscale_act_->setStatusTip(tr("Convert image to grayscale"));

  connect(to_grayscale_act_, &QAction::triggered, this,
          &ImageMenu::toGrayscale);
  connect(duplicate_img_act_, &QAction::triggered, this,
          &ImageMenu::duplicateImage);

  addAction(duplicate_img_act_);
  addSeparator();
  addAction(to_grayscale_act_);
}
