#pragma once

#include <QImage>
#include <QPixmap>
#include <QSharedData>
#include <QUndoStack>

class QUndoCommand;

class ProImage : public QObject {
  Q_OBJECT

public:
  explicit ProImage(QObject *parent = nullptr);
  explicit ProImage(const QString &file_path, QObject *parent = nullptr);
  ProImage(const ProImage &other);
  ProImage(ProImage &&other);

  ProImage &operator=(ProImage other);

  QPixmap getPixmap() const noexcept;
  QString filePath() const noexcept;

  QSize size() const noexcept;
  QRgb pixel(int x, int y) const;
  QRgb pixel(const QPoint &position) const;
  QRect rect() const noexcept;

  QUndoStack &undoStack() { return undo_stack_; };

  friend void swap(ProImage &first, ProImage &second) noexcept;

signals:
  void filePathChanged(const QString &file_path) const;
  // void imageChanged(const ProImage *image);

public slots:
  void open(const QString &file_path);
  bool save() const;
  bool saveAs(const QString &file_path) const;
  void setFilePath(const QString &file_path) const;

  void runCommand(QUndoCommand *command);
  void undo();
  void redo();

private:
  QImage image_;
  mutable QString file_path_;

  QUndoStack undo_stack_;
};
