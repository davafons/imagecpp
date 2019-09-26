#pragma once

#include <QLabel>
#include <QScrollArea>

class HistogramModel;

class ImageViewer : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageViewer(QWidget *parent = 0);
  explicit ImageViewer(const QString &file_name, QWidget *parent = 0);
  ~ImageViewer();

  QString getFilePath() const { return file_path_; }

signals:
  void pixelInformation(const QPoint& point, const QColor& color);

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;

private:
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  QImage loaded_image_;
  QLabel *display_{new QLabel()};

  QString file_path_{""};
  HistogramModel *histogram_{nullptr};
};
