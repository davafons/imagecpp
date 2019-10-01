#pragma once

#include <QObject>

class ProImage;

class ImageManager : public QObject {
  Q_OBJECT

signals:
  void imageOpened(ProImage *image);
  void imageSaved(const ProImage *image);
  void imageDuplicated(const ProImage *duplicated_image);

public slots:
  void open();
  void save(const ProImage *image);
  void saveAs(const ProImage *image, QString file_path = "");

  void duplicate(const ProImage *image);

  // private:
  //   static ProImage *active_image;

private:
  QString filters_ = tr("Image Files(*.png *.jpg *.jpeg *.bmp)");
};
