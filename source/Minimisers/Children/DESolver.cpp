/**
 * @file DESolver.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 28/02/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */

// Headers
#include "DESolver.h"

#include "Estimates/Manager.h"
#include "Minimisers/Children/DESolver/CallBack.h"

// Namespaces
namespace isam {
namespace minimisers {

/**
 * Default constructor
 */
DESolver::DESolver() {
  parameters_.RegisterAllowed(PARAM_POPULATION_SIZE);
  parameters_.RegisterAllowed(PARAM_CROSSOVER_PROBABILITY);
  parameters_.RegisterAllowed(PARAM_DIFFERENCE_SCALE);
  parameters_.RegisterAllowed(PARAM_MAX_GENERATIONS);
  parameters_.RegisterAllowed(PARAM_TOLERANCE);
  parameters_.RegisterAllowed(PARAM_METHOD);
}

/**
 * Destructor
 */
DESolver::~DESolver() {
}

/**
 * Validate the variables giving to this class
 * from the configuration file
 */
void DESolver::Validate() {
  // Parent validate first
  isam::Minimiser::Validate();

  CheckForRequiredParameter(PARAM_POPULATION_SIZE);
  CheckForRequiredParameter(PARAM_MAX_GENERATIONS);

  population_size_        = parameters_.Get(PARAM_POPULATION_SIZE).GetValue<unsigned>();
  crossover_probability_  = parameters_.Get(PARAM_CROSSOVER_PROBABILITY).GetValue<double>(0.9);
  difference_scale_       = parameters_.Get(PARAM_DIFFERENCE_SCALE).GetValue<double>(0.02);
  max_generations_        = parameters_.Get(PARAM_MAX_GENERATIONS).GetValue<unsigned>();
  tolerance_              = parameters_.Get(PARAM_TOLERANCE).GetValue<double>();
  method_                 = parameters_.Get(PARAM_METHOD).GetValue<string>();

  if (crossover_probability_ > 1.0 || crossover_probability_ < 0.0) {
    LOG_ERROR(parameters_.location(PARAM_CROSSOVER_PROBABILITY) << ": crossover_probability must be between 0.0 and 1.0. You entered: " << crossover_probability_);
  }
}

/**
 * Execute our DE Solver minimiser engine
 */
void DESolver::Execute() {
  estimates::Manager& estimate_manager = estimates::Manager::Instance();

  vector<double>  lower_bounds;
  vector<double>  upper_bounds;
  vector<double>  start_values;

  vector<EstimatePtr> estimates = estimate_manager.GetObjects();
  for (EstimatePtr estimate : estimates) {
    if (!estimate->enabled())
      continue;

    lower_bounds.push_back(estimate->lower_bound());
    upper_bounds.push_back(estimate->upper_bound());
    start_values.push_back(estimate->value());

    if (estimate->value() < estimate->lower_bound()) {
      LOG_ERROR("When starting the DESolver minimiser the starting value (" << estimate->value() << ") for estimate "
          << estimate->parameter() << " was less than the lower bound (" << estimate->lower_bound() << ")");
    } else if (estimate->value() > estimate->upper_bound()) {
      LOG_ERROR("When starting the DESolver minimiser the starting value (" << estimate->value() << ") for estimate "
          << estimate->parameter() << " was greater than the upper bound (" << estimate->upper_bound() << ")");
    }
  }

  // Setup Engine
  desolver::CallBack solver = desolver::CallBack(start_values.size(), population_size_, tolerance_);
  solver.Setup(start_values, lower_bounds, upper_bounds, kBest1Exp, difference_scale_, crossover_probability_);

  // Solver
  solver.Solve(max_generations_);
}

} /* namespace minimisers */
} /* namespace isam */