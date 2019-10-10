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
  void toGrayscale();
  void duplicateImage();

private:
  QAction *to_grayscale_act_;
  QAction *duplicate_img_act_;
};

} // namespace imagecpp
