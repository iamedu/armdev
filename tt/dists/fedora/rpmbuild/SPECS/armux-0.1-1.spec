Name:		armux
Version:	0.1
Release:	1%{?dist}
Summary:	Simulator for arm

Group:		Development/Tools
License:	GPL
URL:		http://code.google.com/p/armdev/	
Source0:	http://armdev.googlecode.com/files/armux-0.1.tar.bz2
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:	readline-devel >= 5.2
Requires:	readline >= 5.2

%description
Armux has the objective of simulating arm based processors starting with the at91sam9260, but designed to be portable nonetheless, it is designed to be extensible, so you'll be able to write you own classes to plug in you microcontroller. It is designed for Linux and Python2.6 so be sure you have these requirements. 

%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%files -f archivos
%doc README



%changelog

