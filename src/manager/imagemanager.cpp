#include "imagemanager.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

void ImageManager::open() {
  qInfo() << "Selecting an image path to open";

  QString file_path =
      QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);

  qInfo() << "File selected: " << file_path;

  if (!file_path.isEmpty()) {
    Document *document = new Document(new Image(file_path), this);
    Q_CHECK_PTR(document);

    document->setFilePath(file_path);

    qInfo() << "Document object created:" << document;

    emit imageOpened(document);
  }
}

void ImageManager::save(Document *document) {
  saveAs(document, document->filePath());
}

void ImageManager::saveAs(Document *document, QString file_path) {
  if (!document) {
    return;
  }

  if (file_path.isEmpty()) {
    file_path =
        QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);
    document->setFilePath(file_path);
  }

  if (!document->image()->saveAs(file_path)) {
    // TODO: Specify why image couldn't be saved
    // QMessageBox::critical(this, tr("Save As... error"),
    //                       tr("Couldn't save image!"));
  } else {
    qDebug() << "Image saved";

    emit imageSaved(document, file_path);
  }
}

void ImageManager::duplicate(Document *other) {
  if (!other) {
    return;
  }

  Document *duplicated_image = new Document(*other);

  emit imageOpened(duplicated_image);
}

} // namespace imagecpp
