%module "math"

%{
#include <pybind11/pybind11.h>
%}
%init %{
    /* Get registered types from other pybind11 modules */
    pybind11::detail::get_internals();
%}

%include Angle.i
%include GaussMarkovProcess.i
%include Helpers.i
%include Rand.i
%include Vector2.i
%include Vector3.i
%include Vector4.i
%include Color.i
%include Pose3.i
%include Quaternion.i
%include Line2.i
%include Line3.i
%include Matrix3.i
%include Matrix4.i
%include Filter.i
%include MovingWindowFilter.i
%include PID.i
%include RollingMean.i
%include RotationSpline.i
%include SemanticVersion.i
%include SignalStats.i
%include Spline.i
%include Temperature.i
%include MaterialType.i
%include Material.i
%include Triangle.i
%include Kmeans.i
%include Vector3Stats.i
%include MassMatrix3.i
%include AxisAlignedBox.i
%include Plane.i
%include Frustum.i
%include Inertial.i
%include OrientedBox.i
%include Sphere.i
%include SphericalCoordinates.i
%include StopWatch.i
%include Box.i
%include Cylinder.i
%include DiffDriveOdometry.i
//%include Vertex.i
