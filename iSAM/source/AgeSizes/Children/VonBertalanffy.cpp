/**
 * @file VonBertalanffy.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 14/08/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 */

// headers
#include "VonBertalanffy.h"

#include "SizeWeights/Manager.h"

// namespaces
namespace isam {
namespace agesizes {

/**
 * default constructor
 */
VonBertalanffy::VonBertalanffy() {
  parameters_.RegisterAllowed(PARAM_LINF);
  parameters_.RegisterAllowed(PARAM_K);
  parameters_.RegisterAllowed(PARAM_T0);
  parameters_.RegisterAllowed(PARAM_SIZE_WEIGHT);

  RegisterAsEstimable(PARAM_LINF, &linf_);
  RegisterAsEstimable(PARAM_K, &k_);
  RegisterAsEstimable(PARAM_T0, &t0_);
}

/**
 *
 */
void VonBertalanffy::DoValidate() {
  CheckForRequiredParameter(PARAM_LINF);
  CheckForRequiredParameter(PARAM_K);
  CheckForRequiredParameter(PARAM_T0);

  linf_ = parameters_.Get(PARAM_LINF).GetValue<double>();
  k_    = parameters_.Get(PARAM_K).GetValue<double>();
  t0_   = parameters_.Get(PARAM_T0).GetValue<double>();

  if (linf_ <= 0.0)
    LOG_ERROR(parameters_.location(PARAM_LINF) << "(" << linf_ << ") cannot be less than or equal to 0.0");
  if (k_ <= 0.0)
    LOG_ERROR(parameters_.location(PARAM_K) << "(" << k_ << ") cannot be less than or equal to 0.0");
}

/**
 *
 */
void VonBertalanffy::DoBuild() {
  size_weight_ = sizeweights::Manager::Instance().GetSizeWeight(size_weight_label_);
  if (!size_weight_)
    LOG_ERROR(parameters_.location(PARAM_SIZE_WEIGHT) << "(" << size_weight_label_ << ") could not be found. Have you defined it?");
}

/**
 *
 */
Double VonBertalanffy::mean_size(unsigned age) const {
  if ((-k_ * (age - t0_)) > 10)
    LOG_ERROR("Fatal error in age-size relationship: exp(-k*(age-t0)) is enormous. The k or t0 parameters are probably wrong.");

  Double size = linf_ * (1 - exp(-k_ * (age * t0_)));
  if (size < 0.0)
    return 0.0;

  return size;
}

/**
 *
 */
Double VonBertalanffy::mean_weight(unsigned age) const {
  Double size = this->mean_size(age);
  return size_weight_->mean_weight(size);
}

} /* namespace agesizes */
} /* namespace isam */