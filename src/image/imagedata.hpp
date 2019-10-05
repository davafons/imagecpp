#pragma once

#include <QObject>
#include <QUndoStack>
#include <QVBoxLayout>
#include <QWidget>

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

public slots:
  void setFilePath(QString file_path) {
    file_path_ = file_path;
    emit filePathChanged(file_path);
  }

protected:
  static int next_id_;

private:
  int id_{next_id_++};

  QString file_path_;

  ProImage *image_{nullptr};
  QUndoStack *undo_stack_{new QUndoStack()};
};
