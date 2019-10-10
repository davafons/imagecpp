#include "document.hpp"

#include <QDebug>
#include <QFileInfo>
#include <QUndoStack>

#include "image/image.hpp"

namespace imagecpp {

int Document::next_id_ = 0;

Document::Document(Image *image, QObject *parent)
    : QObject(parent), image_(image), undo_stack_(new QUndoStack()) {}

Document::~Document() { delete undo_stack_; }

Document::Document(const Document &other) {
  QFileInfo other_file_path(other.filePath());
  file_path_ = QString(other_file_path.completeBaseName() + "_copy." +
                       other_file_path.completeSuffix());

  image_ = new Image(*other.image_);
  undo_stack_ = new QUndoStack();
}

Image *Document::copyImage() const { return image_->copy(); }

void Document::setFilePath(QString file_path) {
  file_path_ = file_path;
  emit filePathChanged(file_path);
}

void Document::setImage(Image *image) {
  qInfo() << "Replacing image" << image_ << "with" << image;

  image_ = image;
  emit imageUpdated(image);
}

} // namespace imagecpp
