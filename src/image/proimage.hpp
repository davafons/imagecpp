#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>

class ProImage : public QObject {
  Q_OBJECT

public:
  explicit ProImage() = default;
  explicit ProImage(const QString &file_path);
  ProImage(const ProImage &other);
  ProImage(ProImage &&other);
  virtual ~ProImage() = default;

  ProImage &operator=(ProImage other);

  QPixmap getPixmap() const noexcept;
  QString filePath() const noexcept;

  QSize size() const noexcept;
  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  QRect rect() const noexcept;

  friend void swap(ProImage &first, ProImage &second) noexcept;

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
