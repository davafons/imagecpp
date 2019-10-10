#pragma once

#include <QImage>
#include <QPixmap>

// Forward declarations
class QUndoCommand;

namespace imagecpp {

/*
 *
 */
class ProImage : public QObject {
  Q_OBJECT

public:
  explicit ProImage(const QString &file_path);
  ProImage(int width, int height, QImage::Format format);

  ProImage(const ProImage &other);
  ProImage(ProImage &&other);

  ProImage &operator=(ProImage other);

  QPixmap getPixmap() const noexcept;

  ProImage *copy() const;

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

  friend void swap(ProImage &first, ProImage &second) noexcept;

  static ProImage *empty(const ProImage &other);

public slots:
  void open(const QString &file_path);
  bool saveAs(const QString &file_path) const;

private:
  QImage image_;
};
} // namespace imagecpp
