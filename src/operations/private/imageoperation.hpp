#pragma once

#include <QObject>
#include <QRect>
#include <QString>
#include <QUndoCommand>

#include "image/histogram.hpp"

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

  virtual int exec() const;

  QString name() const;
  QUndoCommand* command();

  const Image* newImage();
  const Image* oldImage() const;

  const Histogram& newHistogram();
  const Histogram& oldHistogram() const;

  QRect selection() const;

  bool isImageRealtimeUpdateToggled() const;
  bool isHistogramRealtimeUpdateToggled() const;

  bool isNewImageUpToDate() const;
  bool isNewHistogramUpToDate() const;

public slots:
  void toggleImageRealtimeUpdate(bool toggled);
  void toggleHistogramRealtimeUpdate(bool toggled);

  void setName(const QString& name);

signals:
  void propertyChanged();
  void imageRealtimeUpdateToggled(bool toggled);
  void histogramRealtimeUpdateToggled(bool toggled);

  void newImageGenerated(const Image* new_image);
  void newHistogramGenerated(const Histogram& histogram);

protected:
  virtual void imageOperationImpl(Image* new_image) = 0;

private:
  void generateNewImage();
  void generateNewHistogram();

private:
  Image* new_image_{nullptr};
  const Image* old_image_{nullptr};

  Histogram new_image_histogram_;
  Histogram old_image_histogram_;

  Document* referenced_document_{nullptr};

  QString name_{"undefined-operation"};

  bool image_realtime_update_toggled_{true};
  bool histogram_realtime_update_toggled_{false};

  bool new_image_up_to_date_{false};
  bool new_histogram_up_to_date_{false};

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
