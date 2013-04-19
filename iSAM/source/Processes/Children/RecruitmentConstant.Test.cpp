/**
 * @file RecruitmentConstant.Test.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 4/04/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */
#ifdef TESTMODE

// Headers
#include "RecruitmentConstant.h"

#include <iostream>

#include "Processes/Factory.h"
#include "TimeSteps/Factory.h"
#include "TimeSteps/Manager.h"
#include "Partition/Partition.h"
#include "TestResources/TestFixtures/BasicModel.h"

// Namespaces
namespace isam {
namespace processes {

using std::cout;
using std::endl;
using isam::testfixtures::BasicModel;

TEST_F(BasicModel, Processes_Constant_Recruitment) {

  vector<string> categories   = { "immature.male", "immature.female" };
  vector<string> proportions  = { "0.6", "0.4" };

  isam::ProcessPtr process = processes::Factory::Create(PARAM_RECRUITMENT, PARAM_CONSTANT);
  process->parameters().Add(PARAM_LABEL, "recruitment", __FILE__, __LINE__);
  process->parameters().Add(PARAM_TYPE, "constant", __FILE__, __LINE__);
  process->parameters().Add(PARAM_CATEGORIES, categories, __FILE__, __LINE__);
  process->parameters().Add(PARAM_PROPORTIONS, proportions, __FILE__, __LINE__);
  process->parameters().Add(PARAM_R0, "100000", __FILE__, __LINE__);
  process->parameters().Add(PARAM_AGE, "1", __FILE__, __LINE__);

  isam::base::ObjectPtr time_step = timesteps::Factory::Create();
  time_step->parameters().Add(PARAM_LABEL, "step_one", __FILE__, __LINE__);
  time_step->parameters().Add(PARAM_PROCESSES, "recruitment", __FILE__, __LINE__);

  Model::Instance()->Start();

  partition::Category& immature_male   = Partition::Instance().category("immature.male");
  partition::Category& immature_female = Partition::Instance().category("immature.female");

  // Verify blank partition
  for (unsigned i = 0; i < immature_male.data_.size(); ++i)
    EXPECT_DOUBLE_EQ(0.0, immature_male.data_[i]) << " where i = " << i << "; age = " << i + immature_male.min_age_;
  for (unsigned i = 0; i < immature_female.data_.size(); ++i)
    EXPECT_DOUBLE_EQ(0.0, immature_female.data_[i]) << " where i = " << i << "; age = " << i + immature_female.min_age_;


  /**
   * Do 1 iteration of the model then check the categories to see if
   * the recruitment was successful
   */
  Model::Instance()->FullIteration();

  EXPECT_DOUBLE_EQ(900000, immature_male.data_[0]);
  EXPECT_DOUBLE_EQ(600000, immature_female.data_[0]);

  for (unsigned i = 1; i < immature_male.data_.size(); ++i)
    EXPECT_DOUBLE_EQ(0.0, immature_male.data_[i]) << " where i = " << i << "; age = " << i + immature_male.min_age_;
  for (unsigned i = 1; i < immature_female.data_.size(); ++i)
    EXPECT_DOUBLE_EQ(0.0, immature_female.data_[i]) << " where i = " << i << "; age = " << i + immature_female.min_age_;
}

} /* namespace processes */
} /* namespace isam */


#endif /* TESTMODE */