#include "../include/xml/Markup.h"
#include<windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
#include "cmWin32ProcessExecution.h"
#include <tinyxml.h>

void AddLog(LPCTSTR lpstrLog,...);

void copyXML (TiXmlDocument* doc, CMarkup* pXml) {

	TiXmlHandle hdl(doc);

	TiXmlElement *elem; // = hdl.FirstChildElement().Element();
	TiXmlNode *pChild;

	for( elem = hdl.FirstChildElement().Element();
		elem;
		elem = elem->NextSiblingElement() ) {

		pXml->AddElem(elem->Value());
		pXml->IntoElem();


		for ( pChild = elem->FirstChild(); pChild != 0; pChild = pChild->IterateChildren(pChild)) {


			if (pChild->FirstChild() != NULL) {

				if (!pXml->AddElemNV(pChild->Value(), pChild->FirstChild()->Value())) {
					AddLog("Failed to save %s: %s", pChild->Value(), pChild->FirstChild()->Value());
				}
				pXml->ResetChildPos();
			}
		}

		pXml->OutOfElem();
	}

}

void scanApps (CMarkup*	pXml) {

	std::string output;
	std::string cmd;
	std::string fileName;


	CMarkup x;

	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	if((hFind = FindFirstFile("scripts\\*", &FindFileData)) != INVALID_HANDLE_VALUE){
		do{

			cmd = "";	
			
			fileName = FindFileData.cFileName;

			if (fileName.size()>4) {

				if (fileName.compare(fileName.size()-4,4,".vbs") == 0) {
					cmd.append("cscript //nologo ");
					cmd.append("scripts\\");
					cmd.append(fileName);
				} else if (fileName.compare(fileName.size()-4,4,".exe") == 0) {
					printf("exe\n");
					cmd.append("scripts\\");
					cmd.append(fileName);
				}

				if (cmd.size()> 1) {
					AddLog("runs: %s\n", cmd.c_str());


					cmWin32ProcessExecution resProc;

					if (!resProc.StartProcess(cmd.c_str(), NULL, false)) {
						AddLog("StartProcess failed");
					} else {

						resProc.Wait(20000);
						output = resProc.GetOutput();
						
						TiXmlDocument *doc = new TiXmlDocument();

						AddLog("From Script: '%s'", output.c_str());

						if (!doc->Parse(output.c_str())) {

							AddLog("Failed to parse XML");

						} else {
							
							copyXML(doc, pXml);
							
						}
					}
				}
			}
		} while(FindNextFile(hFind, &FindFileData));
		FindClose(hFind);

	}
}

