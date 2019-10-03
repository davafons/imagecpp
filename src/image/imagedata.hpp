#pragma once

#include "image/imagedisplayarea.hpp"
#include <QObject>
#include <QUndoStack>
#include <QVBoxLayout>
#include <QWidget>

class ProImage;

/*
 * Cant have ProImage ownership
 */
class ImageData : public QObject {
public:
  ImageData(ProImage *image = nullptr, QObject *parent = nullptr);
  ImageData(const ImageData &data);
  virtual ~ImageData() = default;

  ProImage *image() { return image_; }
  int id() const noexcept { return id_; }

protected:
  static int next_id_;

private:
  int id_{next_id_++};

  ProImage *image_{nullptr};
  QUndoStack undo_stack_;
};
