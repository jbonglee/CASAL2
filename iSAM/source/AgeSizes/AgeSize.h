/**
 * @file AgeSize.h
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
#ifndef AGESIZE_H_
#define AGESIZE_H_

// headers
#include "BaseClasses/Object.h"

// namespaces
namespace isam {

/**
 * class definition
 */
class AgeSize : public isam::base::Object {
public:
  AgeSize();
  virtual                     ~AgeSize();
  void                        Validate() { DoValidate(); };
  void                        Build() { DoBuild(); };
  void                        Reset() { DoReset(); };

  virtual void                DoValidate() = 0;
  virtual void                DoBuild() = 0;
  virtual void                DoReset() = 0;

  // accessors
  virtual Double              mean_size(unsigned age) const = 0;
  virtual Double              mean_weight(unsigned age) const = 0;
};

// typedef
typedef boost::shared_ptr<AgeSize> AgeSizePtr;

} /* namespace isam */
#endif /* AGESIZE_H_ */