//==============================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory NG Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence Version 2.0
// http://www.gnu.org/ or Licence.txt
//==============================================================================


REQUIREMENTS
============

- NSIS 2.46 or higher (http://nsis.sourceforge.net)
- NSIS TextReplace plugin (https://nsis.sourceforge.io/TextReplace_plugin)


BUILDING STEPS
==============

Project is divided into 4 components:
- instOCS.nsi: this is privilegied installer which requires administrator privileges.
               It install certificate and plugins, and starts agent installer with
			   provided command line options.
- 1runas.nsi: this is the All-In-One installer which embbed certifcate, plugins, and
              agent setup, and is able to start privilgied installer under specified
			  account. It is included as source in OcsPackage.exe, and compiled to
			  create All-In-One package.
- ListBox.nsi: this a component to select plugins. It is launched by OcsPackager.
- OcsPackager.nsi: this is the packager. It embbed instOCS.exe, ListBox.exe, NSIS 
                   compiler and 1runas.nsi script, and create All-In-One by customizing 
				   and compiling 1runas.nsi script with user provided options.

So, to build the project, you must compile components in the following order:
1 instOCS.nsi
2 ListBox.nsi
3 OcsPackager.nsi


We hope it will works for you !

OCS Inventory Team