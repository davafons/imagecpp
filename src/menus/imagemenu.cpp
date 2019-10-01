#include "imagemenu.hpp"

#include <QFileDialog>

ImageMenu::ImageMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent) {

  duplicate_img_act_ = new QAction(tr("Duplicate image"), this);
  duplicate_img_act_->setStatusTip(
      tr("Duplicate current image and create a new window"));

  to_grayscale_act_ = new QAction(tr("To grayscale"), this);
  to_grayscale_act_->setStatusTip(tr("Convert image to grayscale"));

  addAction(duplicate_img_act_);
  addSeparator();
  addAction(to_grayscale_act_);
}
