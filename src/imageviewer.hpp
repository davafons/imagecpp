#pragma once

#include <QLabel>
#include <QScrollArea>

class ImageViewer : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageViewer(QWidget *parent = 0);
  explicit ImageViewer(const QString &file_name, QWidget *parent = 0);

public slots:
  void openImage(const QString &file_path);

private:
  QImage loaded_image_;
  QLabel *display_{new QLabel()};

  QString file_path_{""};
};
