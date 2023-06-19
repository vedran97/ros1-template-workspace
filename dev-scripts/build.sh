#! /bin/sh

build_type="$1"
package_name="$3"
build_test="$2"

jobs=3
parrallelPkgs=3
memlimit=50

DCMAKE_C_FLAGS="-Wall -Wextra -Wpedantic -Wno-unused-parameter"
DCMAKE_BUILD_TYPE=""
package_select=""
MAKE_ARGS=""

echo ${build_type} ${package_name}

if [ $# -eq 2 ]
then 
    echo "Building All Packages"
    package_select=""
else
    echo "Building Package [$package_name]"
    package_select="$package_name"
fi

if [ "$build_type" = "Release" ]
then
    echo "Using Release Configuration"
    DCMAKE_BUILD_TYPE="RelWithDebInfo"
else
    echo "Using Debug Configuration"
    DCMAKE_BUILD_TYPE="Debug"
fi

if [ "$build_test" = "Y" ]
then
    echo "Building tests"
    MAKE_ARGS=tests
fi

COMPLETE_BUILD_ARGS="${package_select} --jobs ${jobs} --parallel-packages ${parrallelPkgs} --mem-limit ${memlimit}% --cmake-args -DCMAKE_C_FLAGS=${DCMAKE_C_FLAGS} -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --make-args ${MAKE_ARGS}"

catkin build ${COMPLETE_BUILD_ARGS}
./dev-scripts/concat.sh
echo "Script has finished executing"


