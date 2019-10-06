#pragma once

#include <QObject>
#include <QUndoStack>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

class ProImage;

/*
 * Cant have ProImage ownership
 */
class ImageData : public QObject {
  Q_OBJECT
public:
  ImageData(ProImage *image = nullptr, QObject *parent = nullptr);
  ImageData(const ImageData &data);
  virtual ~ImageData() = default;

  int id() const noexcept { return id_; }
  QString filePath() const { return file_path_; }

  ProImage *image() { return image_; }
  QUndoStack *undoStack() { return undo_stack_; }

signals:
  void filePathChanged(const QString &file_path);
  void imageChanged(const ProImage *image);

public slots:
  void setFilePath(QString file_path);
  void setImage(ProImage *image);

protected:
  static int next_id_;

private:
  int id_{next_id_++};

  QString file_path_;

  ProImage *image_{nullptr};
  QUndoStack *undo_stack_{new QUndoStack()};
};
