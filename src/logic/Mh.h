#pragma once

#include <vector>

namespace mcss::bbeess {
class Mh {
 private:
  std::vector<double> model_params_;
  std::vector<std::vector<double>> mh_trace_;

 protected:
  void InitParams();
  void Transition();
  void Estimate();

 public:
  Mh();
  ~Mh();
};
}  // namespace mcss::bbeess
