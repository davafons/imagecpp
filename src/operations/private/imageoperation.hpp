#pragma once

#include <QColor>
#include <QObject>
#include <QUndoCommand>

#include "image/image.hpp"

// TODO: Remove
#include <QDebug>

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

  const Image *preview();
  QUndoCommand *command();
  bool isLiveUpdateActive() const { return live_update_; }

signals:
  void imageUpdated(const Image *image);
  void propertyChanged();

public slots:
  void toggleLiveUpdate(bool toggled);

protected slots:
  virtual void applyImageOperation() = 0;

protected:
  void setName(const QString &name) { name_ = name; }

private:
  void generateTargetImage();

protected:
  Image *const target_image_;
  const Image *const old_image_;

private:
  Document *const data_;

  QString name_;

  bool up_to_date_ = false;
  bool live_update_ = true;

  class ImageCommand;
};

class ImageOperation::ImageCommand : public QUndoCommand {
public:
  ImageCommand(const QString &name, Document *data,
               const Image *property_modified_image, const Image *old_image);

  virtual void redo() override;
  virtual void undo() override;

private:
  Document *const data_;
  const Image *const target_image_;
  const Image *const old_image_;
};

} // namespace imagecpp
