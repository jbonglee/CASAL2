/**
 * @file None.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 24/07/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * << Add Description >>
 */
#ifndef LENGTHWEIGHTS_NONE_H_
#define LENGTHWEIGHTS_NONE_H_

// headers
#include "LengthWeights/LengthWeight.h"

// namespaces
namespace niwa {
namespace lengthweights {

/**
 * class definition
 */
class None : public niwa::LengthWeight {
public:
  // methods
  None();
  virtual                     ~None() = default;
  void                        DoValidate() override final { };
  void                        DoBuild() override final { };
  void                        DoReset() override final { };

  // accessors
  Double                      mean_weight(Double size, const string &distribution, Double cv) const override final { return 1.0; }
};

} /* namespace lengthweights */
} /* namespace niwa */
#endif /* LENGTHWEIGHTS_NONE_H_ */