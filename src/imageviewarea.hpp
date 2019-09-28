#pragma once

#include <QScrollArea>

#include "imagedisplay.hpp"

class HistogramModel;

class ImageViewArea : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageViewArea(QWidget *parent = 0);
  explicit ImageViewArea(const QString &file_name, QWidget *parent = 0);
  ~ImageViewArea();

  QString getFilePath() const { return file_path_; }

  HistogramModel *getHistogram() const { return histogram_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;

  void zoomIn();
  void zoomOut();
  void normalSize();

private:
  void mousePressEvent(QMouseEvent *event) override {
    if (event->buttons() & Qt::RightButton) {
      last_point_ = event->pos();
    }
  }

  void mouseMoveEvent(QMouseEvent *event) override {
    if (event->buttons() & Qt::RightButton) {
      display_->move(display_->pos() + (event->pos() - last_point_));
      last_point_ = event->pos();
    }
  }
  void adjustScrollBars(float scale_factor);

private:
  ImageDisplay *display_{new ImageDisplay()};
  QImage *loaded_image_;

  QString file_path_{""};
  HistogramModel *histogram_{nullptr};

  QPoint last_point_;
};
