#pragma once

#include <QObject>
#include <QRect>
#include <QString>
#include <QUndoCommand>

namespace imagecpp {

class Document;
class Histogram;
class Image;

class ImageOperation : public QObject {
  Q_OBJECT

public:
  explicit ImageOperation(Document* document,
                          const QString& name = "undefined-operation");

  virtual ~ImageOperation() = default;

  QString name() const;
  QUndoCommand* command();

  const Image* newImage();
  const Image* oldImage() const;
  const Document* referencedDocument() const;

  const Histogram* newHistogram() const;
  const Histogram* oldHistogram() const;

  QRect selection() const;

  bool isRealtimeUpdateToggled() const;
  bool isNewImageUpToDate() const;

public slots:
  void toggleRealtimeUpdate(bool toggled);

  void setName(const QString& name);

  int exec() const;

signals:
  void propertyChanged();
  void realtimeUpdatetoggled(bool toggled);

protected:
  virtual void imageOperationImpl(Image* new_image) = 0;

private:
  void generateNewImage();

private:
  Image* new_image_{nullptr};
  const Image* old_image_{nullptr};
  Document* referenced_document_{nullptr};

  QString name_{"undefined-operation"};
  bool new_image_up_to_date_{false};
  bool realtime_update_toggled_{true};

  class ImageCommand;
};

/*!
 *
 *
 *
 *
 *
 *
 *
 *
 */

class ImageOperation::ImageCommand : public QUndoCommand {
public:
  ImageCommand(const QString& command_name,
               Document* document,
               const Image* property_modified_image,
               const Image* old_image);

  virtual void redo() override;
  virtual void undo() override;

private:
  Document* const document_;
  const Image* const target_image_;
  const Image* const old_image_;
};

}  // namespace imagecpp
