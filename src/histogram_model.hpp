#pragma once

#include <QImage>

#include <array>

class HistogramModel {
public:
  explicit HistogramModel(const QImage &image);

private:
  void buildHistogram();

private:
  const QImage &image_;

  std::array<int, 256> hr_{0};
  std::array<int, 256> hg_{0};
  std::array<int, 256> hb_{0};
};
