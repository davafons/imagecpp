#include "imagedisplayarea.hpp"

#include <QDebug>
#include <QDialog>
#include <QHoverEvent>
#include <QPainter>
#include <QScrollBar>
#include <QTimeLine>

#include "image/image.hpp"

namespace imagecpp {

// TODO: Fix this class

ImageDisplayArea::ImageDisplayArea(QWidget *parent)
    : QScrollArea(parent), image_ref_(nullptr) {
  // Set widgets attributes and options
  target_.setAttribute(Qt::WA_Hover);  // Allow hover events
  target_.setScaledContents(true);

  x_axis_ = new QValueAxis();
  x_axis_->setRange(0, 1);
  x_axis_->setLabelFormat("%d");
  x_axis_->setTickCount(5);

  y_axis_ = new QValueAxis();
  y_axis_->setRange(0, 256);
  y_axis_->setLabelFormat("%d");
  y_axis_->setTickCount(5);

  chart_ = new QChart();
  r_series_ = new QBarSeries();
  g_series_ = new QBarSeries();
  b_series_ = new QBarSeries();
  chart_->addSeries(r_series_);
  chart_->addSeries(g_series_);
  chart_->addSeries(b_series_);

  // chart_->addAxis(x_axis_, Qt::AlignBottom);
  chart_->addAxis(y_axis_, Qt::AlignLeft);
  chart_view_ = new QChartView(chart_);
  chart_view_->setRenderHint(QPainter::Antialiasing);

  profile_dialog = new QDialog(this);

  QVBoxLayout *l = new QVBoxLayout();
  l->addWidget(chart_view_);

  profile_dialog->setLayout(l);

  verticalScrollBar()->setEnabled(false);
  horizontalScrollBar()->setEnabled(false);

  // Set widgets style
  setBackgroundRole(QPalette::Dark);
  setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  target_.setStyleSheet("background: url(:/img/png_pat_dark.png) repeat;");

  // Instal event filters
  target_.installEventFilter(this);

  setWidget(&target_);

  connect(this,
          &ImageDisplayArea::profileSelection,
          this,
          &ImageDisplayArea::calculateProfile);
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
  selection_draw_area_.fill(Qt::transparent);

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
  selection_draw_area_.fill(Qt::transparent);

  recalculateResult();

  // Save current position of the image on the area
  QPoint target_old_pos = target_.pos();

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

void ImageDisplayArea::setDrawingFigure(Figure figure) {
  drawing_figure_ = figure;

  if (drawing_figure_ == Figure::RECT) {
    toggle_selection_ = true;
    profile_dialog->hide();
  } else {
    toggle_selection_ = false;
    profile_dialog->show();
  }
}

void ImageDisplayArea::toggleImageSelection(bool toggle) {
  toggle_selection_ = toggle;
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

    QPainter painter(&selection_draw_area_);
    selection_draw_area_.fill(Qt::transparent);

    painter.setPen(QPen(Qt::red, 5));

    auto normalize = [this](QPoint p) { return (p - target_.pos()) / scale_factor_; };

    QPoint a = normalize(last_clicked_point_);
    QPoint b = normalize(event->pos());

    switch (drawing_figure_) {
      case Figure::RECT:
        painter.drawRect(rect);
        break;

      case Figure::LINE:
        painter.drawLine(a, b);

        emit profileSelection(a, b, image_ref_);
        break;
    }
    painter.end();

    recalculateResult();

    if (toggle_selection_) {
      emit selectionCreated(rect);
    }
  }

  QScrollArea::mouseMoveEvent(event);
}

void ImageDisplayArea::mouseReleaseEvent(QMouseEvent *event) {
  if (rect_selection_toggled_ && event->button() == Qt::LeftButton) {
    QRect rect = createSelectionRect(last_clicked_point_, event->pos());

    QPainter painter(&selection_draw_area_);
    selection_draw_area_.fill(Qt::transparent);

    painter.setPen(QPen(Qt::red, 5));

    auto normalize = [this](QPoint p) { return (p - target_.pos()) / scale_factor_; };

    QPoint a = normalize(last_clicked_point_);
    QPoint b = normalize(event->pos());

    switch (drawing_figure_) {
      case Figure::RECT:
        painter.drawRect(rect);
        break;

      case Figure::LINE:
        painter.drawLine(a, b);

        emit profileSelection(a, b, image_ref_);

        break;
    }

    painter.end();

    recalculateResult();

    if (toggle_selection_) {
      emit selectionCreated(rect);
    }
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

void ImageDisplayArea::keyPressEvent(QKeyEvent *event) {

  switch (event->key()) {
    case Qt::Key::Key_R:
      setDrawingFigure(Figure::RECT);
      break;

    case Qt::Key::Key_T:
      setDrawingFigure(Figure::LINE);
      break;
  }

  QScrollArea::keyPressEvent(event);
}

// TODO: This is such a bad method name, yknow
void ImageDisplayArea::recalculateResult() {
  QPainter painter(&result_image_);
  painter.setCompositionMode(QPainter::CompositionMode_Source);

  painter.fillRect(result_image_.rect(), Qt::transparent);

  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  painter.drawPixmap(0, 0, image_ref_->getPixmap());
  painter.setCompositionMode(QPainter::CompositionMode_Xor);
  painter.drawImage(0, 0, selection_draw_area_);
  painter.end();

  target_.setPixmap(QPixmap::fromImage(result_image_));
}

QRect ImageDisplayArea::createSelectionRect(QPoint a, QPoint b) {
  a = (a - target_.pos()) / scale_factor_;
  b = (b - target_.pos()) / scale_factor_;

  a.setX(std::max(a.x(), 0));
  a.setY(std::max(a.y(), 0));
  b.setX(std::min(b.x(), image_ref_->width()));
  b.setY(std::min(b.y(), image_ref_->height()));

  QRect rect(a, b);
  rect = rect.normalized();

  if (rect.width() <= 1 / scale_factor_ && rect.height() <= 1 / scale_factor_) {
    rect = QRect(0, 0, 0, 0);
  }

  return rect;
}

void ImageDisplayArea::calculateProfile(QPoint s, QPoint e, const Image *image) {

  QBarSet *r = new QBarSet("Red");
  r->setColor(Qt::red);
  r->setBorderColor(Qt::red);
  QBarSet *g = new QBarSet("Green");
  g->setColor(Qt::green);
  g->setBorderColor(Qt::green);
  QBarSet *b = new QBarSet("Blue");
  b->setColor(Qt::blue);
  b->setBorderColor(Qt::blue);

  int x0 = s.x();
  int y0 = s.y();
  int x1 = e.x();
  int y1 = e.y();

  bool steep = false;

  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);

    steep = true;
  }

  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int dx = x1 - x0;
  int dy = y1 - y0;

  int derror2 = std::abs(dy) * 2;
  int error2 = 0;

  int y = y0;

  for (int x = x0; x <= x1; ++x) {
    if (steep) {
      QRgb color = image->pixel(y, x);
      *r << qRed(color);
      *g << qGreen(color);
      *b << qBlue(color);
    } else {
      QRgb color = image->pixel(x, y);
      *r << qRed(color);
      *g << qGreen(color);
      *b << qBlue(color);
    }

    error2 += derror2;

    if (error2 > dx) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2;
    }
  }

  // Graph generation
  r_series_->clear();
  r_series_->append(r);

  g_series_->clear();
  g_series_->append(g);

  b_series_->clear();
  b_series_->append(b);

  chart_->createDefaultAxes();

  chart_->axes()[1]->setRange(0, 255);
}

}  // namespace imagecpp
