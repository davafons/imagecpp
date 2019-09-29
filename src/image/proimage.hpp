#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>

class ProImage : public QSharedData {
public:
  ProImage();
  ProImage(const QString &file_path) { open(file_path); }

  QPixmap getPixmap() const { return QPixmap::fromImage(image_); }

  QSize size() const { return image_.size(); }
  QRgb pixel(int x, int y) const { return image_.pixel(x, y); }
  QRgb pixel(const QPoint &position) const { return image_.pixel(position); }
  QRect rect() const { return image_.rect(); }

public slots:
  void open(const QString &file_path) { image_ = QImage(file_path); }

private:
  QImage image_{};
};
