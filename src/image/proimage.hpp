#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>

class ProImage : public QObject {
  Q_OBJECT

public:
  explicit ProImage() = default;
  explicit ProImage(const QString &file_path);
  virtual ~ProImage() = default;

  QPixmap getPixmap() const;
  QString filePath() const;

  QSize size() const;
  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  QRect rect() const;

signals:
  void filePathChanged(const QString &file_path);

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;
  void setFilePath(const QString &file_path);

private:
  QImage image_;
  QString file_path_;
};
