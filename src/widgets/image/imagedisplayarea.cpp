#include "imagedisplayarea.hpp"

#include <QHoverEvent>
#include <QPainter>
#include <QScrollBar>
#include <QTimeLine>

#include "image/image.hpp"

namespace imagecpp {

ImageDisplayArea::ImageDisplayArea(QWidget *parent)
    : QScrollArea(parent), image_ref_(nullptr) {
  // Set widgets attributes and options
  target_.setAttribute(Qt::WA_Hover);  // Allow hover events
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

float ImageDisplayArea::scaleFactor() const {
  return scale_factor_;
}
const Image *ImageDisplayArea::image() const {
  return image_ref_;
}

void ImageDisplayArea::onImageOpened(const Image *image) {
  qInfo() << "Setting image" << image << "on the display";
  // Reset attributes
  image_ref_ = image;
  scale_factor_ = 1.0f;

  result_image_ = QImage(image_ref_->size(), QImage::Format_ARGB32_Premultiplied);
  selection_draw_area_ =
      QImage(image_ref_->size(), QImage::Format_ARGB32_Premultiplied);

  // Fit image to the window frame
  fitOnFrame();

  // Display image at full size
  recalculateResult();

  emit imageOpened(image_ref_);
}

void ImageDisplayArea::onImageUpdated(const Image *image) {
  image_ref_ = image;

  result_image_ = QImage(image_ref_->size(), QImage::Format_ARGB32_Premultiplied);
  selection_draw_area_ =
      QImage(image_ref_->size(), QImage::Format_ARGB32_Premultiplied);

  // Save current position of the image on the area
  QPoint target_old_pos = target_.pos();

  recalculateResult();
  target_.resize(scale_factor_ * image_ref_->size());

  // Restore the image position
  target_.move(target_old_pos);

  emit imageUpdated(image_ref_);
}

void ImageDisplayArea::resetSize() {
  resize(1.0f);
}

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
  if (event->buttons() & (Qt::LeftButton | Qt::RightButton)) {
    last_clicked_point_ = event->pos();
  }

  QScrollArea::mousePressEvent(event);
}

void ImageDisplayArea::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) {
    target_.move(target_.pos() + (event->pos() - last_clicked_point_));
    last_clicked_point_ = event->pos();
  }

  if (event->buttons() & Qt::LeftButton) {
    QRect rect = createSelectionRect(last_clicked_point_, event->pos());

    emit selectionCreated(rect);
  }

  QScrollArea::mouseMoveEvent(event);
}

void ImageDisplayArea::mouseReleaseEvent(QMouseEvent *event) {
  if (rect_selection_toggled_ && event->button() == Qt::LeftButton) {
    QRect rect = createSelectionRect(last_clicked_point_, event->pos());

    emit selectionCreated(rect);
  }

  QScrollArea::mouseReleaseEvent(event);
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

void ImageDisplayArea::recalculateResult() {
  QPainter painter(&result_image_);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.fillRect(result_image_.rect(), Qt::transparent);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  painter.drawPixmap(0, 0, image_ref_->getPixmap());
  painter.end();

  target_.setPixmap(QPixmap::fromImage(result_image_));  // TODO: Change
}

QRect ImageDisplayArea::createSelectionRect(QPoint a, QPoint b) {
  a = (a - target_.pos()) / scale_factor_;
  b = (b - target_.pos()) / scale_factor_;

  std::max(a.x(), 0);
  std::max(a.y(), 0);
  std::min(b.x(), image_ref_->width());
  std::min(b.y(), image_ref_->height());

  QRect rect(a, b);
  rect = rect.normalized();

  if (rect.width() <= 1 / scale_factor_ && rect.height() <= 1 / scale_factor_) {
    rect = QRect(0, 0, 0, 0);
  }

  return rect;
}

}  // namespace imagecpp
