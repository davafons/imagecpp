#pragma once

#include <QLabel>
#include <QScrollArea>

namespace imagecpp {

// Forward declarations
class Image;

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
  const Image *image() const;

signals:
  void pixelInformation(const QPoint &point, const QColor &color);
  void scaleFactorChanged(float scale_factor);
  void imageSizeChanged(const QSize &new_size);

  void imageOpened(const Image *image);
  void imageUpdated(const Image *image);

  void selectionCreated(const QRect& rect);

public slots:
  void onImageOpened(const Image *image);
  void onImageUpdated(const Image *image);

  void resetSize();
  void resize(float scale_factor);
  void fitOnFrame();

protected:
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

private:
  void recalculateResult();

  QRect createSelectionRect(QPoint a, QPoint b);

private:
  const Image *image_ref_;
  QLabel target_;

  QImage result_image_;
  QImage selection_draw_area_;

  float scale_factor_{1.0f};
  QPoint last_clicked_point_{0, 0};
  int numScheduledScalings_{0};

  bool rect_selection_toggled_{true};
};

}  // namespace imagecpp
