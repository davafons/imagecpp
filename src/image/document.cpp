#include "document.hpp"

#include <QDebug>
#include <QFileInfo>
#include <QUndoStack>

#include "image/image.hpp"

namespace imagecpp {

int Document::next_id_ = 0;

Document::Document(Image *image, QObject *parent)
    : QObject(parent), image_(image), undo_stack_(new QUndoStack()),
      histogram_(new Histogram()) {

  // On image changed -> generate new histogram
  connect(this, &Document::imageChanged, histogram_,
          &Histogram::generateHistogram);

  connect(histogram_, &Histogram::histogramChanged, this,
          &Document::histogramChanged);

  setImage(image);
}

Document::~Document() {
  delete undo_stack_;
  delete histogram_;
}

Document::Document(const Document &other) {
  QFileInfo other_file_path(other.filePath());
  file_path_ = QString(other_file_path.completeBaseName() + "_copy." +
                       other_file_path.completeSuffix());

  image_ = other.copyImage();
  undo_stack_ = new QUndoStack();
  histogram_ = new Histogram(*other.histogram());
}

Image *Document::copyImage() const { return image_->copy(selection()); }

void Document::setFilePath(QString file_path) {
  file_path_ = file_path;

  emit filePathChanged(file_path);
}

void Document::setImage(Image *image) {
  image_ = image;

  if (image) {
    dimensions_ = image_->size();
  } else {
    dimensions_ = QSize();
  }

  emit imageChanged(image);
}

void Document::setSelection(const QRect &selection) {
  selection_ = selection;

  emit selectionChanged(selection_);

  qDebug() << "Selection on document" << selection_;
}

} // namespace imagecpp
