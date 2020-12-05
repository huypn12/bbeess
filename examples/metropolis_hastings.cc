

#include <random>
#include <string>

namespace mcss::bbeess {
class Settings {
 private:
  std::string model_path_;
  std::string props_path_;
};
}  // namespace mcss::bbeess

namespace mcss::bbeess {
class DtBeesLinearModel {
 private:
  std::string prism_model_path_;
  std::string prism_props_path_;

 protected:
  void LoadModelAndPropFiles();
  void BuildRationalFuncs();

  void MhInit();
  void MhTransition();
  void MhEstimate();

 public:
  DtBeesLinearModel();
  ~DtBeesLinearModel();

  void Execute();
  void Simulated();
};
}  // namespace mcss::bbeess

std::random_device gRandomDevice;

void Setup() {}
void Shutdown() {}

int main(int argc, char **argv) {
  Setup();
  Shutdown();
  return 0;
}