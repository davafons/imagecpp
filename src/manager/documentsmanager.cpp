#include "documentsmanager.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "image/document.hpp"
#include "image/image.hpp"

namespace imagecpp {

void DocumentsManager::open() {
  qInfo() << "Selecting an image path to open";

  QString file_path =
      QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);

  qInfo() << "File selected: " << file_path;

  if (!file_path.isEmpty()) {
    Document *document = new Document(new Image(file_path));
    Q_CHECK_PTR(document);

    document->setFilePath(file_path);

    qInfo() << "Document object created:" << document;

    emit newDocumentOpened(document);
  }
}

void DocumentsManager::save(Document *document) const {
  if (!document) {
    return;
  }

  saveAs(document, document->filePath());
}

void DocumentsManager::saveAs(Document *document, QString file_path) const {
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

    emit documentSaved(document, file_path);
  }
}

void DocumentsManager::duplicate(Document *other) const {
  if (!other) {
    return;
  }

  Document *duplicated_document = new Document(*other);

  emit newDocumentOpened(duplicated_document);
}

} // namespace imagecpp
