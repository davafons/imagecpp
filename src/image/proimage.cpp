#include "proimage.hpp"

#include <QDebug>
#include <QUndoCommand>
#include <QUndoStack>

ProImage::ProImage(const QString &file_path) {
  setFilePath(file_path);

  open(file_path_);
}

ProImage::ProImage(const ProImage &other) {
  image_ = other.image_.copy();
  // undo_stack_ = other.undo_stack_; // TODO: Manage memory
  file_path_ = other.file_path_;
}

ProImage::ProImage(ProImage &&other) { swap(*this, other); }

ProImage &ProImage::operator=(ProImage other) {
  swap(*this, other);

  return *this;
}

QPixmap ProImage::getPixmap() const noexcept {
  return QPixmap::fromImage(image_);
}

QString ProImage::filePath() const noexcept { return file_path_; }

QSize ProImage::size() const noexcept { return image_.size(); }

QRgb ProImage::pixel(int x, int y) const { return image_.pixel(x, y); }

QRgb ProImage::pixel(const QPoint &position) const {
  return image_.pixel(position);
}

QRect ProImage::rect() const noexcept { return image_.rect(); }

void swap(ProImage &first, ProImage &second) noexcept {
  using std::swap;

  swap(first.image_, second.image_);
  swap(first.file_path_, second.file_path_);
}

void ProImage::open(const QString &file_path) {
  setFilePath(file_path);
  image_ = QImage(file_path);
}

bool ProImage::save() const { return saveAs(file_path_); }

bool ProImage::saveAs(const QString &file_path) const {
  if (file_path != file_path_) {
    setFilePath(file_path);
  }

  return image_.save(file_path);
}

void ProImage::setFilePath(const QString &file_path) const {
  file_path_ = file_path;

  emit filePathChanged(file_path);
}

void ProImage::runCommand(QUndoCommand *command) { undo_stack_.push(command); }

void ProImage::undo() { undo_stack_.undo(); }
void ProImage::redo() { undo_stack_.redo(); }
