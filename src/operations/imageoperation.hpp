#pragma once

#include <QColor>
#include <QUndoCommand>

#include "image/imagedata.hpp"
#include "image/proimage.hpp"

class ImageData;
class ProImage;

class ImageOperation : public QObject {
  Q_OBJECT

public:
  ImageOperation(ImageData *data, const QString &name = "");
  virtual ~ImageOperation() = default;

  QString name() const { return name_; }
  const ProImage *preview();

  QUndoCommand *command();

signals:
  void imageChanged(const ProImage *image);
  void propertyChanged();

private slots:
  void generateImage();

protected:
  virtual QRgb pixelOperation(int x, int y, QRgb color) const = 0;

  void setName(const QString &name) { name_ = name; }

private:
  QString name_;

  ImageData *const data_;

  ProImage *const modified_image_;
  const ProImage *const old_image_;

  bool up_to_date_ = false;
  bool real_time_ = true;

private:
  class ImageCommand : public QUndoCommand {
  public:
    ImageCommand(const QString &name, ImageData *data,
                 const ProImage *modified_image, const ProImage *old_image)
        : QUndoCommand(name), data_(data), modified_image_(modified_image),
          old_image_(old_image) {}

    virtual void redo() override { data_->setImage(modified_image_->copy()); }
    virtual void undo() override { data_->setImage(old_image_->copy()); }

  private:
    ImageData *const data_;
    const ProImage *const modified_image_;
    const ProImage *const old_image_;
  };
};
