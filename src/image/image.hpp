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
  // Construction and copy
  explicit Image(const QString &file_path);
  Image(int width, int height, QImage::Format format);

  Image(const Image &other);
  Image(Image &&other);

  Image &operator=(Image other);

  // Iterators
  // QRgb *begin();
  // const QRgb *begin() const;
  // const QRgb *cbegin() const;
  //
  // QRgb *end();
  // const QRgb *end() const;
  // const QRgb *cend() const;

  // Image Operations
  QPixmap getPixmap() const noexcept;
  Image *copy() const;

  // Properties
  int width() const noexcept;
  int height() const noexcept;
  QSize size() const noexcept;
  QRect rect() const noexcept;
  QImage::Format format() const noexcept;
  size_t pixelCount() const noexcept;

  // Pixel Operations
  QRgb *bits();
  QRgb *scanLine(int i);
  const QRgb *constBits() const;
  const QRgb *constScanLine(int i) const;

  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  void setPixel(int x, int y, uint index_or_rgb);
  void setPixel(const QPoint &position, uint index_or_rgb);

  QColor pixelColor(const QPoint &position) const;
  QColor pixelColor(int x, int y) const;
  void setPixelColor(int x, int y, const QColor &color);
  void setPixelColor(const QPoint &position, const QColor &color);

  // Static functions
  static Image *empty(const Image &other);

  // Friend functions
  friend void swap(Image &first, Image &second) noexcept;

public slots:
  void open(const QString &file_path);
  bool saveAs(const QString &file_path) const;

private:
  QImage image_;
};

} // namespace imagecpp
