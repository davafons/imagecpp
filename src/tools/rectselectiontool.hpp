#pragma once

#include <QDebug>
#include <QObject>
#include <QPoint>

class RectSelectionTool : public QObject {
  Q_OBJECT

public:
  RectSelectionTool(QObject *parent = nullptr);
  virtual ~RectSelectionTool() = default;

  virtual bool eventFilter(QObject *object, QEvent *event) override;

signals:
  void selectionCreated(QRect rect) const;

private:
  void createSelection(QPoint start_point, QPoint end_point) const;

private:
  QPoint last_clicked_point_;
};
