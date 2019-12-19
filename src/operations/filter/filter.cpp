#include "filter.hpp"

#include <QDebug>
#include <sstream>

namespace imagecpp {

Filter::Filter(Document* document) : FilterOperation(document, tr("Filter")) {
  kernel_str_ = "1 1 1\n1 1 1\n1 1 1";
}

std::string Filter::kernelString() const {
  return kernel_str_;
}

void Filter::fillKernel() {
  qDebug() << "Kernel filled";

  std::stringstream kernel_stream(kernel_str_);
  std::string line;

  std::vector<std::vector<int>> new_kernel;

  while (std::getline(kernel_stream, line, '\n')) {
    std::stringstream line_stream(line);
    std::string token;

    std::vector<int> kernel_row;

    while (line_stream >> token) {
      qDebug() << std::stoi(token);

      kernel_row.push_back(std::stoi(token));
    }

    qDebug() << "Newline";

    new_kernel.push_back(kernel_row);
  }

  kernel_ = new_kernel;
}

void Filter::setKernelFromString(const std::string& kernel_str) {
  kernel_str_ = kernel_str;

  qDebug() << "Kernel str\n" << kernel_str_.c_str();

  emit propertyChanged();
}

}  // namespace imagecpp
