#include "imagedisplayarea.hpp"
#include "proimage.hpp"

#include <QDebug>
#include <QHoverEvent>
#include <QTimeLine>

ImageDisplayArea::ImageDisplayArea(QWidget *parent) : QScrollArea(parent) {
  // Set widgets attributes and options
  target_.setAttribute(Qt::WA_Hover); // Allow hover events
  target_.setScaledContents(true);

  // Set widgets style
  setBackgroundRole(QPalette::Dark);
  target_.setStyleSheet("background: url(:/img/png_pat_dark.png) repeat;");

  // Instal event filters
  target_.installEventFilter(this);

  setWidget(&target_);
}

float ImageDisplayArea::scaleFactor() const { return scale_factor_; }
const ProImage *ImageDisplayArea::image() const { return image_ref_; }

void ImageDisplayArea::setImage(const ProImage *image) {
  // Reset attributes
  image_ref_ = image;
  scale_factor_ = 1.0f;
  setWindowTitle(image_ref_->filePath());

  // Display image at full size
  target_.setPixmap(image_ref_->getPixmap());
  target_.resize(image_ref_->size());

  // Connections
  connect(image_ref_, &ProImage::filePathChanged, this,
          &ImageDisplayArea::setWindowTitle);
  // connect(image_ref_, &ProImage::imageChanged, this,
  //         &ImageDisplayArea::onImageChanged);
}

void ImageDisplayArea::onImageChanged(const ProImage *image) {
  setImage(image);
}

void ImageDisplayArea::resetSize() { setScaleFactor(1.0f); }

void ImageDisplayArea::setScaleFactor(float scale_factor) {
  scale_factor_ = scale_factor;

  target_.resize(scale_factor_ * image_ref_->size());

  emit scaleFactorChanged(scale_factor_);
  emit imageSizeChanged(target_.size());
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
      qreal factor = 1.0 + qreal(numScheduledScalings_) / 50.0;
      scale_factor_ = factor;
      target_.resize(image_ref_->size() * factor);
    });

    connect(anim, &QTimeLine::finished, this, [this] { sender()->~QObject(); });

    anim->start();

    return;
  }

  QScrollArea::wheelEvent(event);
}
