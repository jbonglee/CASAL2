/**
 * @file Factory.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 24/07/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 */

// headers
#include "Factory.h"

#include "SizeWeights/Children/Basic.h"
#include "SizeWeights/Children/None.h"

// namespaces
namespace isam {
namespace sizeweights {

/**
 *
 */
SizeWeightPtr Factory::Create(const string& block_type, const string& object_type) {
  SizeWeightPtr result;

  if (block_type == PARAM_SIZE_WEIGHT && object_type == PARAM_NONE) {
    result = SizeWeightPtr(new None());
  } else if (block_type == PARAM_SIZE_WEIGHT && object_type == PARAM_BASIC) {
    result = SizeWeightPtr(new Basic());
  }

  return result;
}

} /* namespace sizeweights */
} /* namespace isam */