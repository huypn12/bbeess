#include <storm-parsers/api/storm-parsers.h>
#include <storm-parsers/parser/PrismParser.h>
#include <storm/api/storm.h>
#include <storm/modelchecker/results/CheckResult.h>
#include <storm/modelchecker/results/ExplicitQuantitativeCheckResult.h>
#include <storm/storage/jani/Property.h>
#include <storm/storage/prism/Program.h>
#include <storm/utility/initialize.h>

class Experiment {
 private:
  std::string model_file_path_;
  std::string props_file_path_;

 protected:
  void LoadModelPropertyFiles();
  bool Check();
};

typedef storm::models::sparse::Dtmc<storm::RationalFunction> Dtmc;
typedef storm::modelchecker::SparseDtmcPrctlModelChecker<Dtmc> DtmcModelChecker;

void Experiment::LoadModelPropertyFiles() {
  auto program = storm::parser::PrismParser::parse(model_file_path_);
  // Code snippet assumes a Dtmc
  assert(program.getModelType() == storm::prism::Program::ModelType::DTMC);
  // Then parse the properties, passing the program to give context to some
  // potential variables.
  auto properties =
      storm::api::parsePropertiesForPrismProgram(props_file_path_, program);
  // Translate properties into the more low-level formulae.
  auto formulae = storm::api::extractFormulasFromProperties(properties);

  // storm::parser::PrismParser::parseFromString(const std::string& input)
}

bool Experiment::Check() {
  // Assumes that the model is in the prism program language format and parses
  // the program.
  auto program = storm::parser::PrismParser::parse(model_file_path_);
  // Code snippet assumes a Dtmc
  assert(program.getModelType() == storm::prism::Program::ModelType::DTMC);
  // Then parse the properties, passing the program to give context to some
  // potential variables.
  auto properties =
      storm::api::parsePropertiesForPrismProgram(props_file_path_, program);
  // Translate properties into the more low-level formulae.
  auto formulae = storm::api::extractFormulasFromProperties(properties);

  // Now translate the prism program into a DTMC in the sparse format.
  // Use the formulae to add the correct labelling.
  auto model =
      storm::api::buildSparseModel<storm::RationalFunction>(program, formulae)
          ->template as<Dtmc>();

  // Create a model checker on top of the sparse engine.
  auto checker = std::make_shared<DtmcModelChecker>(*model);
  // Create a check task with the formula. Run this task with the model checker.
  auto result =
      checker->check(storm::modelchecker::CheckTask<storm::logic::Formula,
                                                    storm::RationalFunction>(
          *(formulae[0]), true));
  assert(result->isExplicitQuantitativeCheckResult());
  // Use that we know that the model checker produces an explicit quantitative
  // result
  auto quantRes =
      result->asExplicitQuantitativeCheckResult<storm::RationalFunction>();
  // Now compare the result at the first initial state of the model with 0.5.
  std::cout << quantRes[*model->getInitialStates().begin()] << std::endl;
  // return quantRes[*model->getInitialStates().begin()]> 0.5;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Needs exactly 2 arguments: model file and property"
              << std::endl;
    return 1;
  }

  // Init loggers
  storm::utility::setUp();
  // Set some settings objects.
  storm::settings::initializeAll("storm-starter-project",
                                 "storm-starter-project");

  // Call function
  auto result = check(argv[1], argv[2]);
  // And print result
  std::cout << "Result > 0.5? " << (result ? "yes" : "no") << std::endl;
}
