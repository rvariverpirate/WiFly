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

echo_and_run cd "/home/tripp/Workspaces/src/rosserial/src/rosserial_vex_cortex"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/tripp/Workspaces/src/rosserial/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/tripp/Workspaces/src/rosserial/install/lib/python2.7/dist-packages:/home/tripp/Workspaces/src/rosserial/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/tripp/Workspaces/src/rosserial/build" \
    "/usr/bin/python2" \
    "/home/tripp/Workspaces/src/rosserial/src/rosserial_vex_cortex/setup.py" \
    build --build-base "/home/tripp/Workspaces/src/rosserial/build/rosserial_vex_cortex" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/tripp/Workspaces/src/rosserial/install" --install-scripts="/home/tripp/Workspaces/src/rosserial/install/bin"
