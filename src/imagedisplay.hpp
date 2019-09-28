#pragma once

#include <QHoverEvent>
#include <QLabel>

class ImageDisplay : public QLabel {
  Q_OBJECT

public:
  ImageDisplay(QWidget *parent = nullptr);

  bool event(QEvent *event) override;

signals:
  void pixelInformation(const QPoint &point, const QColor &color);
  void scaleFactorChanged(float scale_factor);

public slots:
  void setImage(const QImage *image);

  void zoomIn();
  void zoomOut();
  void normalSize();
  void setImageScale(float scale_factor);

private:
  const QImage *loaded_image_{nullptr};
  float scale_factor_{1.0f};
};
