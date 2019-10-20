#pragma once

#include <QFileDialog>
#include <QObject>
#include <QUndoCommand>
#include <QUndoStack>

#include "histogram.hpp"

// Forward declarations

namespace imagecpp {

// Forward declarations
class Image;

/*
 * The intent of this class is to represent a document, an object that ties
 * together an image, a histogram and a history of changes. Also has information
 * about the image (name, filepath, format...)
 */
class Document : public QObject {
  Q_OBJECT

public:
  explicit Document(Image *image = nullptr, QObject *parent = nullptr);

  Document(const Document &document);
  virtual ~Document();

  // Property getters
  int id() const noexcept { return id_; }
  QString filePath() const noexcept { return file_path_; }
  QSize dimensions() const noexcept { return dimensions_; }

  // Object getters
  Image *image() { return image_; }
  const Image *image() const { return image_; }

  QUndoStack *undoStack() { return undo_stack_; }
  const QUndoStack *undoStack() const { return undo_stack_; }

  Histogram *histogram() { return histogram_; }
  const Histogram *histogram() const { return histogram_; }

  // Functions
  Image *copyImage() const;

signals:
  void filePathChanged(const QString &file_path);
  void imageChanged(const Image *image);
  void histogramChanged(const Histogram *histogram);

public slots:
  void setFilePath(QString file_path);
  void setImage(Image *image);

protected:
  static int next_id_;

private:
  // Unique identifier of the document
  int id_{next_id_++};

  // Document properties
  QString file_path_;
  QSize dimensions_;

  // Document objects
  Image *image_;
  QUndoStack *undo_stack_;
  Histogram *histogram_;
};

} // namespace imagecpp
