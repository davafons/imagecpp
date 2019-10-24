#include "rectselectiontool.hpp"

#include <QEvent>
#include <QMouseEvent>

#include "widgets/image/subwindowsarea.hpp"

namespace imagecpp {

RectSelectionTool::RectSelectionTool(const SubWindowsArea *subwin_area,
                                     QObject *parent)
    : subwin_area_(subwin_area), tracked_widget_(nullptr) {
  // Connect to widget
}

RectSelectionTool::~RectSelectionTool() {
  // Disconnect from widget (RAII)
}

bool RectSelectionTool::eventFilter(QObject *object, QEvent *event) {
  QMouseEvent *mouse_event = dynamic_cast<QMouseEvent *>(event);

  if (mouse_event) {
    if (mouse_event->type() == QEvent::MouseButtonPress) {
      if (mouse_event->buttons() & Qt::LeftButton) {
        last_clicked_point_ = mouse_event->pos();
      }
    }

    if (mouse_event->type() == QEvent::MouseButtonRelease) {
      createSelection(last_clicked_point_, mouse_event->pos());
      last_clicked_point_ = QPoint(0, 0);
    }

    return true;
  }

  return QObject::eventFilter(object, event);
}

void RectSelectionTool::createSelection(QPoint start_point,
                                        QPoint end_point) const {
  QRect rect = QRect(start_point, end_point);
  rect.setWidth(std::abs(rect.width()));
  rect.setHeight(std::abs(rect.height()));

  qDebug() << "Selection created" << rect.width() << rect.height();

  emit selectionCreated(rect);
}

} // namespace imagecpp
