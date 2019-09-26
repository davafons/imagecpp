#pragma once

#include <QLabel>
#include <QScrollArea>

class ImageViewer : public QScrollArea {
  Q_OBJECT

public:
  explicit ImageViewer(QWidget *parent = 0);
  explicit ImageViewer(const QString &file_name, QWidget *parent = 0);

  QString getFilePath() const { return file_path_; }

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;

private:
  QImage loaded_image_;
  QLabel *display_{new QLabel()};

  QString file_path_{""};
};
