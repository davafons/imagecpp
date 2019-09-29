#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>

class ProImage : public QSharedData {
public:
  ProImage() = default;
  ProImage(const QString &file_path);
  virtual ~ProImage() = default;

  QPixmap getPixmap() const;
  QString filePath() const;

  QSize size() const;
  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  QRect rect() const;

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;

private:
  QImage image_;
  QString file_path_;
};
