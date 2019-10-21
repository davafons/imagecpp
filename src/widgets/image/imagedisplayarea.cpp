#include "imagedisplayarea.hpp"

#include <QDebug>
#include <QHoverEvent>
#include <QScrollBar>
#include <QTimeLine>

#include "image/image.hpp"

namespace imagecpp {

ImageDisplayArea::ImageDisplayArea(QWidget *parent)
    : QScrollArea(parent), image_ref_(nullptr) {
  // Set widgets attributes and options
  target_.setAttribute(Qt::WA_Hover); // Allow hover events
  target_.setScaledContents(true);

  verticalScrollBar()->setEnabled(false);
  horizontalScrollBar()->setEnabled(false);

  // Set widgets style
  setBackgroundRole(QPalette::Dark);
  setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  target_.setStyleSheet("background: url(:/img/png_pat_dark.png) repeat;");

  // Instal event filters
  target_.installEventFilter(this);

  setWidget(&target_);
}

float ImageDisplayArea::scaleFactor() const { return scale_factor_; }
const Image *ImageDisplayArea::image() const { return image_ref_; }

void ImageDisplayArea::onImageOpened(const Image *image) {
  qInfo() << "Setting image" << image << "on the display";
  // Reset attributes
  image_ref_ = image;
  scale_factor_ = 1.0f;

  // Fit image to the window frame
  fitOnFrame();

  // Display image at full size
  target_.setPixmap(image_ref_->getPixmap());

  emit imageOpened(image_ref_);
}

void ImageDisplayArea::onImageUpdated(const Image *image) {
  image_ref_ = image;

  // Save current position of the image on the area
  QPoint target_old_pos = target_.pos();

  target_.setPixmap(image_ref_->getPixmap());
  target_.resize(scale_factor_ * image_ref_->size());

  // Restore the image position
  target_.move(target_old_pos);

  emit imageUpdated(image_ref_);
}

void ImageDisplayArea::resetSize() { resize(1.0f); }

void ImageDisplayArea::resize(float scale_factor) {
  if (scale_factor <= 0) {
    scale_factor_ = 0;
    return;
  }

  scale_factor_ = scale_factor;
  numScheduledScalings_ = scale_factor_ * 50;

  target_.resize(scale_factor_ * image_ref_->size());

  emit scaleFactorChanged(scale_factor_);
  emit imageSizeChanged(target_.size());
}

void ImageDisplayArea::fitOnFrame() {
  int longest_side = std::max(image_ref_->width(), image_ref_->height());
  scale_factor_ = float(size().width()) / longest_side;

  resize(scale_factor_);
}

bool ImageDisplayArea::eventFilter(QObject *obj, QEvent *event) {
  if (obj == &target_ && event->type() == QEvent::HoverMove) {
    QHoverEvent *hover_event = static_cast<QHoverEvent *>(event);
    QPoint cursor_pos = hover_event->pos() / scale_factor_;

    if (image_ref_->rect().contains(cursor_pos)) {
      emit pixelInformation(cursor_pos, image_ref_->pixel(cursor_pos));

      return true;
    }
  }
  return QObject::eventFilter(obj, event);
}

void ImageDisplayArea::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) {
    last_clicked_point_ = event->pos();
  }
}

void ImageDisplayArea::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) {
    target_.move(target_.pos() + (event->pos() - last_clicked_point_));
    last_clicked_point_ = event->pos();
  }
}

// TODO: Transform literals to constants?
void ImageDisplayArea::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() & Qt::ControlModifier) {
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    numScheduledScalings_ += numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, &QTimeLine::valueChanged, this, [this](qreal x) {
      qreal factor = qreal(numScheduledScalings_) / 50.0;
      resize(factor);
    });

    connect(anim, &QTimeLine::finished, this, [this] { sender()->~QObject(); });

    anim->start();

    return;
  }

  QScrollArea::wheelEvent(event);
}

} // namespace imagecpp
