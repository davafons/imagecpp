#pragma once

#include <set>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class LinearTransform : public LutOperation {
public:
  class Pair {
  public:
    Pair(int in, int out) : in_(in), out_(out) {}
    int in() const { return in_; }
    int out() const { return out_; }

    friend bool operator<(const Pair &lhs, const Pair &rhs) {
      if (lhs.in() == rhs.in()) {
        return lhs.out() < rhs.out();
      }

      return lhs.in() < rhs.out();
    }

  private:
    int in_;
    int out_;
  };

  // Constructors

  explicit LinearTransform(Document *document,
                           const std::set<Pair> &steps = std::set<Pair>{
                               Pair(0, 0), Pair(255, 255)});

  // Getters and Setters
  void addStep(int in, int out);

  virtual void fillLutTables() override;

private:
  std::set<Pair> steps_;
};

// --- Dialog ---
/*
 *
 */
class LinearTransformConfigDialog
    : public OperationConfigDialog<LinearTransform> {
public:
  explicit LinearTransformConfigDialog(Document *document,
                                       QWidget *parent = nullptr);
  virtual ~LinearTransformConfigDialog() = default;

private:
};

} // namespace imagecpp
