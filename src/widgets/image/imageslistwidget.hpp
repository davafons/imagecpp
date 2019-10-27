#pragma once

#include <QListWidget>

namespace imagecpp {

class Image;

class ImagesListWidget : public QListWidget {
  Q_OBJECT

public:
  ImagesListWidget(QWidget* parent = nullptr);
  virtual ~ImagesListWidget() = default;

signals:
  void imageChanged(const Image* image);

public slots:
  void addImage(const QString& name, const Image* image);

private:
  class ImageItem : public QListWidgetItem {
  public:
    ImageItem(const QString& name, const Image* image)
        : QListWidgetItem(name), image_(image) {}

    const Image* image() const { return image_; }

  private:
    const Image* const image_;
  };
};

}  // namespace imagecpp
