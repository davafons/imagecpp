#pragma once

#include <QDebug>
#include <QObject>
#include <QPoint>

namespace imagecpp {

class SubWindowsArea;

class RectSelectionTool : public QObject {
  Q_OBJECT

public:
  RectSelectionTool(const SubWindowsArea *subwin_area, QObject *parent = nullptr);
  virtual ~RectSelectionTool();

  virtual bool eventFilter(QObject *object, QEvent *event) override;

signals:
  void selectionCreated(const QRect& selection) const;

private:
  void createSelection(QPoint start_point, QPoint end_point) const;

private:
  QPoint last_clicked_point_;

  const SubWindowsArea *subwin_area_;
  QWidget *tracked_widget_;
};

}
