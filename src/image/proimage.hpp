#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>
#include <QUndoStack>

class QUndoCommand;

class ProImage : public QObject {
  Q_OBJECT

public:
  explicit ProImage(QObject *parent = nullptr);
  explicit ProImage(const QString &file_path, QObject *parent = nullptr);
  ProImage(const ProImage &other);
  ProImage(ProImage &&other);

  ProImage &operator=(ProImage other);

  QPixmap getPixmap() const noexcept;

  QSize size() const noexcept;
  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  QRect rect() const noexcept;

  friend void swap(ProImage &first, ProImage &second) noexcept;

signals:
  // void imageChanged(const ProImage *image);

public slots:
  void open(const QString &file_path);
  bool saveAs(const QString &file_path) const;

private:
  QImage image_;
};
