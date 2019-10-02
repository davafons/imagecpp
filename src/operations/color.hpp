#pragma once

#include <QDebug>
#include <QObject>
#include <QUndoCommand>

class ProImage;

class ToGrayscaleCommand : public QUndoCommand {

public:
  ToGrayscaleCommand(const ProImage *old_image)
      : QUndoCommand(QIODevice::tr("To grayscale")), old_image_(old_image) {

      }

  virtual void redo() override { qDebug() << "Redo"; }
  virtual void undo() override { qDebug() << "Undo"; }

private:
  const ProImage *old_image_{nullptr};
  const ProImage *new_image_{nullptr};
};
