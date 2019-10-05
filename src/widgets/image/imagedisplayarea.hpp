#pragma once

#include <QLabel>
#include <QScrollArea>

class ProImage;

/*!
 * \class ImageDisplayArea
 * Area for displaying images with scrollbars, movement and zooming.
 * TODO: Enable/Disable zooming, movement? Fit image to size?
 */
class ImageDisplayArea : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageDisplayArea(QWidget *parent = nullptr);
  virtual ~ImageDisplayArea() = default;

  float scaleFactor() const;
  const ProImage *image() const;

signals:
  void pixelInformation(const QPoint &point, const QColor &color);
  void scaleFactorChanged(float scale_factor);
  void imageSizeChanged(const QSize &new_size);

public slots:
  void setImage(const ProImage *image);
  void onImageChanged(const ProImage *image);

  void resetSize();
  void setScaleFactor(float scale_factor);

protected:
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

private:
  const ProImage *image_ref_;
  QLabel target_;

  float scale_factor_{1.0f};
  QPoint last_clicked_point_{0, 0};
  int numScheduledScalings_{0};
};
