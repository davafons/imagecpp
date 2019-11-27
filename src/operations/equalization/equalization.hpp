#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Equalization : public PointOperation {
  Q_OBJECT

public:
  explicit Equalization(Document *document);
  virtual ~Equalization() = default;

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  const QBarSet* red_ch_{nullptr};
  const QBarSet *green_ch_{nullptr};
  const QBarSet *blue_ch_{nullptr};

  const int K{256};
  const int M;
  const int N;
};

}  // namespace imagecpp
