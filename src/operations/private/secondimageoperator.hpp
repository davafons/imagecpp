#pragma once

#include "operations/private/imageoperation.hpp"

namespace imagecpp {

class Image;

class SecondImageOperator : public QObject {
  Q_OBJECT

public:
  const Image *image() const;

signals:
  void imageChanged(const Image *image);

public slots:
  void setImage(const Image *image);

protected:
  const Image *second_image_{nullptr};
};

}  // namespace imagecpp
