%bcond_without tests
%bcond_without weak_deps

%global __os_install_post %(echo '%{__os_install_post}' | sed -e 's!/usr/lib[^[:space:]]*/brp-python-bytecompile[[:space:]].*$!!g')
%global __provides_exclude_from ^/opt/ros/galactic/.*$
%global __requires_exclude_from ^/opt/ros/galactic/.*$

Name:           ros-galactic-mapviz
Version:        2.2.0
Release:        3%{?dist}%{?release_suffix}
Summary:        ROS mapviz package

License:        BSD
URL:            https://github.com/swri-robotics/mapviz
Source0:        %{name}-%{version}.tar.gz

Requires:       freeglut-devel
Requires:       glew-devel
Requires:       libXi-devel
Requires:       libXmu-devel
Requires:       qt5-qtbase
Requires:       ros-galactic-cv-bridge
Requires:       ros-galactic-geometry-msgs
Requires:       ros-galactic-image-transport
Requires:       ros-galactic-launch-xml
Requires:       ros-galactic-mapviz-interfaces
Requires:       ros-galactic-marti-common-msgs
Requires:       ros-galactic-pluginlib
Requires:       ros-galactic-rclcpp
Requires:       ros-galactic-rqt-gui
Requires:       ros-galactic-rqt-gui-cpp
Requires:       ros-galactic-std-srvs
Requires:       ros-galactic-swri-math-util
Requires:       ros-galactic-swri-transform-util
Requires:       ros-galactic-tf2
Requires:       ros-galactic-tf2-geometry-msgs
Requires:       ros-galactic-tf2-ros
Requires:       yaml-cpp-devel
Requires:       ros-galactic-ros-workspace
BuildRequires:  freeglut-devel
BuildRequires:  glew-devel
BuildRequires:  libXi-devel
BuildRequires:  libXmu-devel
BuildRequires:  pkgconfig
BuildRequires:  qt5-qtbase
BuildRequires:  qt5-qtbase-devel
BuildRequires:  ros-galactic-ament-cmake
BuildRequires:  ros-galactic-cv-bridge
BuildRequires:  ros-galactic-geometry-msgs
BuildRequires:  ros-galactic-image-transport
BuildRequires:  ros-galactic-mapviz-interfaces
BuildRequires:  ros-galactic-marti-common-msgs
BuildRequires:  ros-galactic-pluginlib
BuildRequires:  ros-galactic-rclcpp
BuildRequires:  ros-galactic-rqt-gui
BuildRequires:  ros-galactic-rqt-gui-cpp
BuildRequires:  ros-galactic-std-srvs
BuildRequires:  ros-galactic-swri-math-util
BuildRequires:  ros-galactic-swri-transform-util
BuildRequires:  ros-galactic-tf2
BuildRequires:  ros-galactic-tf2-geometry-msgs
BuildRequires:  ros-galactic-tf2-ros
BuildRequires:  yaml-cpp-devel
BuildRequires:  ros-galactic-ros-workspace
Provides:       %{name}-devel = %{version}-%{release}
Provides:       %{name}-doc = %{version}-%{release}
Provides:       %{name}-runtime = %{version}-%{release}

%description
mapviz

%prep
%autosetup -p1

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/galactic/setup.sh" ]; then . "/opt/ros/galactic/setup.sh"; fi
mkdir -p obj-%{_target_platform} && cd obj-%{_target_platform}
%cmake3 \
    -UINCLUDE_INSTALL_DIR \
    -ULIB_INSTALL_DIR \
    -USYSCONF_INSTALL_DIR \
    -USHARE_INSTALL_PREFIX \
    -ULIB_SUFFIX \
    -DCMAKE_INSTALL_PREFIX="/opt/ros/galactic" \
    -DAMENT_PREFIX_PATH="/opt/ros/galactic" \
    -DCMAKE_PREFIX_PATH="/opt/ros/galactic" \
    -DSETUPTOOLS_DEB_LAYOUT=OFF \
    ..

%make_build

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/galactic/setup.sh" ]; then . "/opt/ros/galactic/setup.sh"; fi
%make_install -C obj-%{_target_platform}

%if 0%{?with_tests}
%check
# Look for a Makefile target with a name indicating that it runs tests
TEST_TARGET=$(%__make -qp -C obj-%{_target_platform} | sed "s/^\(test\|check\):.*/\\1/;t f;d;:f;q0")
if [ -n "$TEST_TARGET" ]; then
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/galactic/setup.sh" ]; then . "/opt/ros/galactic/setup.sh"; fi
CTEST_OUTPUT_ON_FAILURE=1 \
    %make_build -C obj-%{_target_platform} $TEST_TARGET || echo "RPM TESTS FAILED"
else echo "RPM TESTS SKIPPED"; fi
%endif

%files
/opt/ros/galactic

%changelog
* Tue Dec 21 2021 P. J. Reed <preed@swri.org> - 2.2.0-3
- Autogenerated by Bloom

* Tue Dec 21 2021 P. J. Reed <preed@swri.org> - 2.2.0-2
- Autogenerated by Bloom

* Wed Nov 17 2021 P. J. Reed <preed@swri.org> - 2.2.0-1
- Autogenerated by Bloom

