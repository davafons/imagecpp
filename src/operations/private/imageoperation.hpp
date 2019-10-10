#pragma once

#include <QColor>
#include <QObject>
#include <QUndoCommand>

#include "image/proimage.hpp"

namespace imagecpp {

// Forward declarations
class Document;

/*
 *
 */
class ImageOperation : public QObject {
  Q_OBJECT

public:
  ImageOperation(Document *data, const QString &name = "");
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

  Document *const data_;

  ProImage *const modified_image_;
  const ProImage *const old_image_;

  bool up_to_date_ = false;
  bool real_time_ = true;

  class ImageCommand;
};

class ImageOperation::ImageCommand : public QUndoCommand {
public:
  ImageCommand(const QString &name, Document *data,
               const ProImage *modified_image, const ProImage *old_image);

  virtual void redo() override;
  virtual void undo() override;

private:
  Document *const data_;
  const ProImage *const modified_image_;
  const ProImage *const old_image_;
};

} // namespace imagecpp
