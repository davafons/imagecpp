#pragma once

#include <QIntValidator>
#include <QLineEdit>

#include <map>

#include "operations/private/lutoperation.hpp"
#include "operations/private/operationconfigdialog.hpp"

#include <QPushButton>

namespace imagecpp {

// --- Implementation ---

/*
 *
 */
class LinearTransform : public LutOperation {
public:
  // Constructors

  explicit LinearTransform(Document *document,
                           const std::map<int, int> &steps = std::map<int, int>{
                               {0, 0}, {255, 255}});

  // Getters and Setters
  void addStep(int in, int out);
  void removeStep(int in);

  const std::map<int, int> &steps() const { return steps_; }

  virtual void fillLutTables() override;

private:
  std::map<int, int> steps_;
};

// --- Dialog ---
class InOutItem : public QWidget {
  Q_OBJECT

public:
  InOutItem(int in, int out, QWidget *parent = nullptr) : QWidget(parent) {
    QHBoxLayout *hbox = new QHBoxLayout();

    in_edit_ = new QLineEdit(QString::number(in));
    out_edit_ = new QLineEdit(QString::number(out));

    in_edit_->setValidator(new QIntValidator(0, 255, in_edit_));
    out_edit_->setValidator(new QIntValidator(0, 255, out_edit_));

    delete_button_ = new QPushButton(tr("Delete"));

    hbox->addWidget(new QLabel(tr("In")));
    hbox->addWidget(in_edit_);
    hbox->addWidget(new QLabel(tr("Out")));
    hbox->addWidget(out_edit_);
    hbox->addWidget(delete_button_);

    connect(delete_button_, &QPushButton::clicked, this,
            [this] { setParent(nullptr); emit itemDeleted(this); });

    setLayout(hbox);
  }

  int in() const { return in_edit_->text().toInt(); }
  int out() const { return out_edit_->text().toInt(); }

signals:
  void itemDeleted(InOutItem *step);

private:
  QLineEdit *in_edit_;
  QLineEdit *out_edit_;
  QPushButton *delete_button_;
};
/*
 *
 */
class LinearTransformConfigDialog
    : public OperationConfigDialog<LinearTransform> {
  Q_OBJECT

public:
  explicit LinearTransformConfigDialog(Document *document,
                                       QWidget *parent = nullptr);
  virtual ~LinearTransformConfigDialog() = default;

private slots:
  void addStep(int in = 0, int out = 0);

private:
  QVBoxLayout *steps_list_layout_;

  QPushButton *add_button_;
};

} // namespace imagecpp
