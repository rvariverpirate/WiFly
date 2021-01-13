#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/src/rosserial/rosserial_vex_v5"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/install/lib/python2.7/dist-packages:/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/build" \
    "/usr/bin/python2" \
    "/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/src/rosserial/rosserial_vex_v5/setup.py" \
     \
    build --build-base "/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/build/rosserial/rosserial_vex_v5" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/install" --install-scripts="/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/install/bin"
