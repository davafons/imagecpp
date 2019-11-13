#pragma once

#include "operations/private/pointoperation.hpp"

namespace imagecpp {

class Mirror : public PointOperation {
public:
  enum class Direction { Horizontal, Vertical };

public:
  Mirror(Document* document, const Direction& dir = Direction::Horizontal);
  virtual ~Mirror() = default;

  Direction direction() const;

public slots:
  void setDirection(const Direction& dir);

protected:
  virtual QRgb pointOperationImpl(int x, int y, QRgb color) override;

private:
  Direction dir_;
};

}  // namespace imagecpp
