#pragma once

#include <QMenu>

class ImageMenu : public QMenu {
public:
  explicit ImageMenu(const QString &title = tr("&Image"),
                     QWidget *parent = nullptr);
  virtual ~ImageMenu() = default;

  QAction *toGrayscale() const { return to_grayscale_act_; }
  QAction *duplicateImage() const { return duplicate_img_act_; }

private:
  QAction *to_grayscale_act_;
  QAction *duplicate_img_act_;
};
