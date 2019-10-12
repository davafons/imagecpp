#pragma once

#include <QDockWidget>
#include <QVBoxLayout>

class ResizableDockWidget : public QDockWidget {
  Q_OBJECT

public:
  explicit ResizableDockWidget(const QString &title = "", QWidget *parent = 0,
                               Qt::WindowFlags flags = 0);
  virtual ~ResizableDockWidget() = default;

public:
  void setWidget(QWidget *widget);

private:
  QWidget *child_;
  QVBoxLayout *layout_;


};
