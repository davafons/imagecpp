#pragma once

#include <QLabel>
#include <QWidget>

namespace imagecpp {

/*
 *
 */
class PixelInformationWidget : public QWidget {
public:
  explicit PixelInformationWidget(QWidget *parent = nullptr);
  virtual ~PixelInformationWidget() = default;

public slots:
  void onPixelInformationReceived(const QPoint &point, const QColor &color);

private:
  void changeSquareLabelColor(const QString &name = "white");

private:
  QLabel color_square_label_;
  QLabel pixel_info_label_;
};

} // namespace imagecpp
