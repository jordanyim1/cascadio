#include "convert.hpp"
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(cascadio, m) {
  m.doc() = R"pbdoc(
        cascadio
        ---------
        A module for converting STEP, IGES, and BREP files into GLB and OBJ.
    )pbdoc";

  py::enum_<FileType>(m, "FileType")
    .value("UNSPECIFIED", FileType::UNSPECIFIED)
    .value("STEP", FileType::STEP)
    .value("IGES", FileType::IGES)
    .export_values();

  m.def("to_glb", &to_glb,
        R"pbdoc(
Convert a STEP or IGES file to a GLB file.

Parameters
----------
input_path
  The input file to load (STEP or IGES).
output_path
  The path to save the GLB file.
file_type
  Either IGES or STEP (default: STEP)
tol_linear
  How large should linear deflection be allowed.
tol_angular
  How large should angular deflection be allowed.
tol_relative
  Is tol_linear relative to edge length, or an absolute distance?
merge_primitives
  Produce a GLB with one mesh primitive per part.
use_parallel
  Use parallel execution to produce meshes and exports.

)pbdoc",
	py::arg("input_path"),
	py::arg("output_path"),
	py::arg("file_type") = FileType::STEP,
	py::arg("tol_linear") = 0.01,
	py::arg("tol_angular") = 0.5,
	py::arg("tol_relative") = false,
	py::arg("merge_primitives") = true,
	py::arg("use_parallel") = true
	);

  m.def("to_obj",
	&to_obj,
R"pbdoc(
Convert a STEP or IGES file to an OBJ ( and if applicable MTL ) file.

Parameters
----------
input_path
  The input file to load (STEP or IGES).
output_path
  The path to save the OBJ ( and if applicable MTL ) file.
file_type
  Either IGES or STEP (default: STEP)
tol_linear
  How large should linear deflection be allowed.
tol_angular
  How large should angular deflection be allowed.
tol_relative
  Is tol_linear relative to edge length, or an absolute distance?
use_parallel
  Use parallel execution to produce meshes and exports.
use_colors
  Whether to export/use colors/materials from the input file.
  Disabling colors will skip exporting a MTL sidecar file.
  If input doesn't use color/material then no MTL will be exported,
  regardless of 'use_colors'.

)pbdoc",
	py::arg("input_path"),
	py::arg("output_path"),
	py::arg("file_type") = FileType::STEP,
	py::arg("tol_linear") = 0.01,
	py::arg("tol_angular") = 0.5,
	py::arg("tol_relative") = false,
	py::arg("use_parallel") = true,
	py::arg("use_colors") = true
	);

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
