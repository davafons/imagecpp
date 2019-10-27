#include "documentsmanager.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "image/document.hpp"
#include "image/image.hpp"
#include "widgets/image/imageslistwidget.hpp"

namespace imagecpp {

QMap<int, Document *> DocumentsManager::loaded_documents_ = QMap<int, Document *>();

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

    loaded_documents_[document->id()] = document;

    qDebug() << loaded_documents_.size();
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
    file_path = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "~", filters_);
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

  loaded_documents_[duplicated_document->id()] = duplicated_document;

  emit newDocumentOpened(duplicated_document);
}

ImagesListWidget *DocumentsManager::createImagesListWidget(QWidget *parent) {
  ImagesListWidget *images_list = new ImagesListWidget(parent);

  for (const auto &doc : loaded_documents_) {
    images_list->addImage(doc->filePath(), doc->image());
  }

  return images_list;
}

}  // namespace imagecpp
