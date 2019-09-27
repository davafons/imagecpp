#pragma once

#include <QDebug>
#include <QHoverEvent>
#include <QLabel>
#include <QScrollArea>

#include <QMouseEvent>

class HistogramModel;

class ImageDisplay : public QLabel {
  Q_OBJECT
signals:
  void mouseHover(const QPoint &point);

public:
  ImageDisplay(QWidget *parent = nullptr) : QLabel(parent) {
    setAttribute(Qt::WA_Hover);
  }

  bool event(QEvent *event) override {
    if (event->type() == QEvent::HoverMove) {
      // Emit mouse position when hovering the image
      QHoverEvent *hover_event = dynamic_cast<QHoverEvent *>(event);
      emit mouseHover(hover_event->pos());

      return true;
    }

    return QWidget::event(event);
  }
};

class ImageViewer : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageViewer(QWidget *parent = 0);
  explicit ImageViewer(const QString &file_name, QWidget *parent = 0);
  ~ImageViewer();

  QString getFilePath() const { return file_path_; }

signals:
  void pixelInformation(const QPoint &point, const QColor &color);

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;

private:
  QImage loaded_image_;
  ImageDisplay *display_{new ImageDisplay()};

  QString file_path_{""};
  HistogramModel *histogram_{nullptr};
};
