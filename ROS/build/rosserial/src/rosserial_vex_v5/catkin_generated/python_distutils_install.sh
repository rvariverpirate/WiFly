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
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/tripp/Desktop/WiFly/ROS/src/rosserial/src/rosserial_vex_v5"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/tripp/Desktop/WiFly/ROS/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/tripp/Desktop/WiFly/ROS/install/lib/python2.7/dist-packages:/home/tripp/Desktop/WiFly/ROS/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/tripp/Desktop/WiFly/ROS/build" \
    "/usr/bin/python2" \
    "/home/tripp/Desktop/WiFly/ROS/src/rosserial/src/rosserial_vex_v5/setup.py" \
    build --build-base "/home/tripp/Desktop/WiFly/ROS/build/rosserial/src/rosserial_vex_v5" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/tripp/Desktop/WiFly/ROS/install" --install-scripts="/home/tripp/Desktop/WiFly/ROS/install/bin"