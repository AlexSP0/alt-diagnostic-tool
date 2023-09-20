%define _unpackaged_files_terminate_build 1

Name: alt-diagnostic-tool
Version: 0.1.1
Release: alt1

Summary: ALT Diagnostic tool
License: GPLv2+
Group: Other
Url: https://github.com/AlexSP0/alt-diagnostic-tool

BuildRequires: cmake
BuildRequires: rpm-macros-cmake
BuildRequires: cmake-modules
BuildRequires: gcc-c++
BuildRequires: qt5-base-devel
BuildRequires: qt5-declarative-devel
BuildRequires: qt5-tools-devel
BuildRequires: qt5-base-common
BuildRequires: boost-devel-headers
BuildRequires: doxygen

BuildRequires: desktop-file-utils ImageMagick-tools

Requires: alterator-manager
Requires: alterator-module-executor

Source0: %name-%version.tar

%description
ADT (Alt Diagnostic Tool) is a utility for diagnosing software problems using the alterator-interface-diag1 interface.

%prep
%setup -q

%build
%cmake
%cmake_build

%install
%cmakeinstall_std

cd %_cmake__builddir
desktop-file-install --dir=%buildroot%_desktopdir \
                     --set-key Exec --set-value %_bindir/alt-diagnostic-tool \
                     ../setup/adt.desktop

%files
%doc README.md
%doc INSTALL.md

%_bindir/alt-diagnostic-tool
%_desktopdir/adt.desktop

%changelog
* Wed Jun 28 2023 Aleksey Saprunov <sav@altlinux.org> 0.1.1-alt1
- Use alterator-module-executor to get tools and tests

* Wed Dec 07 2022 Vladimir Rubanov <august@altlinux.org> 0.1.0-alt1
- Initial build
