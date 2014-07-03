/**
 * @file Constant.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @date 28/05/2014
 * @section LICENSE
 *
 * Copyright NIWA Science �2014 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * << Add Description >>
 */
#ifndef PROJECTS_CONSTANT_H_
#define PROJECTS_CONSTANT_H_

// headers
#include "Projects/Project.h"

// namespaces
namespace isam {
namespace projects {

/**
 * Class definition
 */
class Constant : public isam::Project {
public:
  Constant();
  virtual                     ~Constant() = default;
  void                        DoValidate() override final;
  void                        DoBuild() override final;
  void                        DoReset() override final;
};

} /* namespace projects */
} /* namespace isam */

#endif /* CONSTANT_H_ */