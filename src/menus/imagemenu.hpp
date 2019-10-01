#pragma once

#include <QMenu>

class ImageMenu : public QMenu {
  Q_OBJECT
public:
  explicit ImageMenu(const QString &title = tr("&Image"),
                     QWidget *parent = nullptr);
  virtual ~ImageMenu() = default;

signals:
  void toGrayscale();
  void duplicateImage();

private:
  QAction *to_grayscale_act_;
  QAction *duplicate_img_act_;
};
