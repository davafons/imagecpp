#include "imagedisplay.hpp"

#include <QDebug>

ImageDisplay::ImageDisplay(QWidget *parent) : QLabel(parent) {
  setAttribute(Qt::WA_Hover);
  setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  setScaledContents(true);

  setStyleSheet("background: url(:/img/png_pat_dark.png) repeat;");
}

bool ImageDisplay::event(QEvent *event) {
  if (event->type() == QEvent::HoverMove) {
    // Emit mouse position when hovering the image
    QHoverEvent *hover_event = dynamic_cast<QHoverEvent *>(event);
    QPoint cursor_position = hover_event->pos() / scale_factor_;

    if (loaded_image_->rect().contains(cursor_position)) {
      emit pixelInformation(cursor_position,
                            loaded_image_->pixel(cursor_position));
    }

    return true;
  }

  return QWidget::event(event);
}

void ImageDisplay::setImage(const QImage *image) {
  loaded_image_ = image;
  scale_factor_ = 1.0f;

  setPixmap(QPixmap::fromImage(*loaded_image_));
  resize(loaded_image_->size());
}

void ImageDisplay::zoomIn() { setImageScale(scale_factor_ + 0.2f); }
void ImageDisplay::zoomOut() { setImageScale(scale_factor_ - 0.2f); }
void ImageDisplay::normalSize() { setImageScale(1.0f); }

void ImageDisplay::setImageScale(float scale_factor) {
  qDebug() << "Scaling image to " << scale_factor;
  scale_factor_ = scale_factor;

  resize(scale_factor_ * loaded_image_->size());

  emit scaleFactorChanged(scale_factor_);
}
