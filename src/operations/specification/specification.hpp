#pragma once

#include "operations/private/lutoperation.hpp"

namespace imagecpp {

class Specification : public LutOperation {
  Q_OBJECT

public:
  explicit Specification(Document *document);
  virtual ~Specification() = default;

public slots:
  void setSecondImage(const Image *image);

protected:
  virtual void fillLutTablesImpl() override;
  virtual void imageOperationImpl(Image *new_image) override;

private:
  const Image *second_image_{nullptr};
  Histogram second_image_histogram_;
};

}  // namespace imagecpp
