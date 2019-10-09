#pragma once

#include <QColor>
#include <QUndoCommand>

class ImageData;
class ProImage;

class ImageOperation : public QUndoCommand {

public:
  ImageOperation(ImageData *data, const QString &name = "");
  virtual ~ImageOperation() = default;

  virtual void undo() override;
  virtual void redo() override;

protected:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const = 0;

  void setOperationName(const QString &name) { setText(name); }

private:
  void calculateImage();

private:
  ImageData *const data_;

  ProImage *const modified_image_;
  ProImage *const old_image_;

  bool operation_done_ = false;
};
