#pragma once

#include <QMap>
#include <QObject>

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

class ImageManager : public QObject {
  Q_OBJECT

signals:
  void imageOpened(ImageData *data);
  void imageSaved(ImageData *data);
  void imageDuplicated(ImageData *data);

public slots:
  void open();
  void save(ImageData *image);
  void saveAs(ImageData *image, QString file_path = "");

  void duplicate(ImageData *other);

  // private:
  //   static ProImage *active_image;

private:
  // QMap<int, ImageData*> loaded_images_;
  QString filters_ = tr("Image Files(*.png *.jpg *.jpeg *.bmp)");
};
