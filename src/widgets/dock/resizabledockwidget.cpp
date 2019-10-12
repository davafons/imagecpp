#include "resizabledockwidget.hpp"

#include <QDebug>
#include <QSizeGrip>

ResizableDockWidget::ResizableDockWidget(const QString &title, QWidget *parent,
                                         Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags), child_(new QWidget()),
      layout_(new QVBoxLayout()) {
  layout_->setContentsMargins(QMargins(0, 0, 0, 0));
  layout_->setSpacing(0);

  child_->setLayout(layout_);
  QDockWidget::setWidget(child_);
}

void ResizableDockWidget::setWidget(QWidget *widget) {
  QSizeGrip *size_grip = new QSizeGrip(widget);
  size_grip->setVisible(false);

  layout_->addWidget(widget);
  layout_->addWidget(size_grip, 0, Qt::AlignBottom | Qt::AlignRight);

  connect(this, &ResizableDockWidget::topLevelChanged, size_grip,
          &QSizeGrip::setVisible);
}
