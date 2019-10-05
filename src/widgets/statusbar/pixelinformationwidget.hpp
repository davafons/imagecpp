#pragma once

#include <QLabel>
#include <QWidget>

class PixelInformationWidget : public QWidget {
public:
  explicit PixelInformationWidget(QWidget *parent = nullptr);
  virtual ~PixelInformationWidget() = default;

public slots:
  void onPixelInformationReceived(const QPoint &point, const QColor &color);

private:
  QLabel color_square_label_;
  QLabel pixel_info_label_;
};
