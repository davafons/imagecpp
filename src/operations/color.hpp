#pragma once

#include <QDebug>
#include <QObject>
#include <QUndoCommand>

class ImageData;
class ProImage;

class ToGrayscaleCommand : public QUndoCommand {

public:
  ToGrayscaleCommand(ImageData *data);

  virtual void redo() override;
  virtual void undo() override;

private:
  ImageData *data_{nullptr}; // Make a const pointer?

  ProImage *modified_image_{nullptr};
  ProImage *old_image_{nullptr};
};
