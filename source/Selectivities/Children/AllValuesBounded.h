/**
 * @file AllValuesBounded.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 14/01/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * The time class represents a moment of time.
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */
#ifndef ALLVALUESBOUNDED_H_
#define ALLVALUESBOUNDED_H_

// Headers
#include "Selectivities/Selectivity.h"

// Namespaces
namespace isam {
namespace selectivities {

/**
 * Class Definition
 */
class AllValuesBounded : public isam::Selectivity {
public:
  // Methods
  AllValuesBounded();
  virtual                     ~AllValuesBounded() {};
  void                        Validate() override final;
  void                        Reset() override final;

private:
  // Members
  unsigned                    low_;
  unsigned                    high_;
  vector<Double>              v_;
};

} /* namespace selectivities */
} /* namespace isam */
#endif /* ALLVALUESBOUNDED_H_ */