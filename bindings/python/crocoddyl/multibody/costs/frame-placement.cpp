///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2018-2020, LAAS-CNRS, University of Edinburgh
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include "python/crocoddyl/multibody/multibody.hpp"
#include "python/crocoddyl/multibody/cost-base.hpp"
#include "crocoddyl/multibody/costs/frame-placement.hpp"

namespace crocoddyl {
namespace python {

void exposeCostFramePlacement() {
  bp::class_<CostModelFramePlacement, bp::bases<CostModelAbstract> >(
      "CostModelFramePlacement",
      bp::init<boost::shared_ptr<StateMultibody>, boost::shared_ptr<ActivationModelAbstract>, FramePlacement, int>(
          bp::args("self", "state", "activation", "Mref", "nu"),
          "Initialize the frame placement cost model.\n\n"
          ":param state: state of the multibody system\n"
          ":param activation: activation model\n"
          ":param Mref: reference frame placement\n"
          ":param nu: dimension of control vector"))
      .def(bp::init<boost::shared_ptr<StateMultibody>, boost::shared_ptr<ActivationModelAbstract>, FramePlacement>(
          bp::args("self", "state", "activation", "Mref"),
          "Initialize the frame placement cost model.\n\n"
          "For this case the default nu is equals to model.nv.\n"
          ":param state: state of the multibody system\n"
          ":param activation: activation model\n"
          ":param Mref: reference frame placement"))
      .def(bp::init<boost::shared_ptr<StateMultibody>, FramePlacement, int>(
          bp::args("self", "state", "Mref", "nu"),
          "Initialize the frame placement cost model.\n\n"
          "For this case the default activation model is quadratic, i.e.\n"
          "crocoddyl.ActivationModelQuad(6).\n"
          ":param state: state of the multibody system\n"
          ":param Mref: reference frame placement\n"
          ":param nu: dimension of control vector"))
      .def(bp::init<boost::shared_ptr<StateMultibody>, FramePlacement>(
          bp::args("self", "state", "Mref"),
          "Initialize the frame placement cost model.\n\n"
          "For this case the default activation model is quadratic, i.e.\n"
          "crocoddyl.ActivationModelQuad(6), and nu is equals to model.nv.\n"
          ":param state: state of the multibody system\n"
          ":param Mref: reference frame placement"))
      .def("calc", &CostModelFramePlacement::calc_wrap,
           CostModel_calc_wraps(bp::args("self", "data", "x", "u"),
                                "Compute the frame placement cost.\n\n"
                                ":param data: cost data\n"
                                ":param x: time-discrete state vector\n"
                                ":param u: time-discrete control input"))
      .def<void (CostModelFramePlacement::*)(const boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&,
                                             const Eigen::VectorXd&)>(
          "calcDiff", &CostModelFramePlacement::calcDiff_wrap, bp::args("self", "data", "x", "u"),
          "Compute the derivatives of the frame placement cost.\n\n"
          ":param data: action data\n"
          ":param x: time-discrete state vector\n"
          ":param u: time-discrete control input\n")
      .def<void (CostModelFramePlacement::*)(const boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&)>(
          "calcDiff", &CostModelFramePlacement::calcDiff_wrap, bp::args("self", "data", "x"))

      .def("createData", &CostModelFramePlacement::createData, bp::with_custodian_and_ward_postcall<0, 2>(),
           bp::args("self", "data"),
           "Create the frame placement cost data.\n\n"
           "Each cost model has its own data that needs to be allocated. This function\n"
           "returns the allocated data for a predefined cost.\n"
           ":param data: shared data\n"
           ":return cost data.")
      .add_property("Mref", bp::make_function(&CostModelFramePlacement::get_Mref, bp::return_internal_reference<>()),
                    &CostModelFramePlacement::set_Mref, "reference frame placement");

  bp::register_ptr_to_python<boost::shared_ptr<CostDataFramePlacement> >();

  bp::class_<CostDataFramePlacement, bp::bases<CostDataAbstract> >(
      "CostDataFramePlacement", "Data for frame placement cost.\n\n",
      bp::init<CostModelFramePlacement*, DataCollectorAbstract*>(
          bp::args("self", "model", "data"),
          "Create frame placement cost data.\n\n"
          ":param model: frame placement cost model\n"
          ":param data: shared data")[bp::with_custodian_and_ward<1, 2, bp::with_custodian_and_ward<1, 3> >()])
      .add_property("r", bp::make_getter(&CostDataFramePlacement::r, bp::return_value_policy<bp::return_by_value>()),
                    "cost residual")
      .add_property("rMf",
                    bp::make_getter(&CostDataFramePlacement::rMf, bp::return_value_policy<bp::return_by_value>()),
                    "error frame placement of the frame")
      .add_property("J", bp::make_getter(&CostDataFramePlacement::J, bp::return_value_policy<bp::return_by_value>()),
                    "Jacobian at the error point")
      .add_property("rJf",
                    bp::make_getter(&CostDataFramePlacement::rJf, bp::return_value_policy<bp::return_by_value>()),
                    "error Jacobian of the frame")
      .add_property("fJf",
                    bp::make_getter(&CostDataFramePlacement::fJf, bp::return_value_policy<bp::return_by_value>()),
                    "local Jacobian of the frame");
}

}  // namespace python
}  // namespace crocoddyl
