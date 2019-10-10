#pragma once

#include <QImage>
#include <QPixmap>

// Forward declarations
class QUndoCommand;

namespace imagecpp {

/*
 *
 */
class Image : public QObject {
  Q_OBJECT

public:
  explicit Image(const QString &file_path);
  Image(int width, int height, QImage::Format format);

  Image(const Image &other);
  Image(Image &&other);

  Image &operator=(Image other);

  QPixmap getPixmap() const noexcept;

  Image *copy() const;

  int width() const noexcept { return image_.width(); }
  int height() const noexcept { return image_.height(); }
  QSize size() const noexcept { return image_.size(); }
  QRect rect() const noexcept { return image_.rect(); }
  QImage::Format format() const noexcept { return image_.format(); }

  QRgb pixel(int x, int y) const { return image_.pixel(x, y); }
  QRgb pixel(const QPoint &position) const { return image_.pixel(position); }

  void setPixel(int x, int y, uint index_or_rgb) {
    image_.setPixel(x, y, index_or_rgb);
  }

  void setPixel(const QPoint &position, uint index_or_rgb) {
    image_.setPixel(position, index_or_rgb);
  }

  QColor pixelColor(const QPoint &position) const {
    return image_.pixelColor(position);
  }
  QColor pixelColor(int x, int y) const { return image_.pixelColor(x, y); }

  void setPixelColor(int x, int y, const QColor &color) {
    image_.setPixelColor(x, y, color);
  }
  void setPixelColor(const QPoint &position, const QColor &color) {
    image_.setPixelColor(position, color);
  }

  friend void swap(Image &first, Image &second) noexcept;

  static Image *empty(const Image &other);

public slots:
  void open(const QString &file_path);
  bool saveAs(const QString &file_path) const;

private:
  QImage image_;
};
} // namespace imagecpp
