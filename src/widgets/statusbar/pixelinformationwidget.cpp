#include "pixelinformationwidget.hpp"

#include <QHBoxLayout>

namespace imagecpp {

PixelInformationWidget::PixelInformationWidget(QWidget *parent)
    : QWidget(parent) {
  color_square_label_.setFixedSize(16, 16);
  changeSquareLabelColor("white");

  QHBoxLayout *layout = new QHBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(&color_square_label_);
  layout->addWidget(&pixel_info_label_);

  setLayout(layout);
}

void PixelInformationWidget::onPixelInformationReceived(const QPoint &point,
                                                        const QColor &color) {
  pixel_info_label_.setText(QString("x: %1 y: %2 \t R: %3 G: %4 B: %5 A: %6")
                                .arg(point.x() + 1)
                                .arg(point.y() + 1)
                                .arg(color.red())
                                .arg(color.green())
                                .arg(color.blue())
                                .arg(color.alpha()));

  changeSquareLabelColor(color.name());
}

void PixelInformationWidget::changeSquareLabelColor(const QString &name) {
  color_square_label_.setStyleSheet(
      QString("background-color: %1; border: 1px solid black;").arg(name));
}

} // namespace imagecpp
