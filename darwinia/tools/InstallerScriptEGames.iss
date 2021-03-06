; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Darwinia
AppVerName=Darwinia v1.42
AppPublisher=eGames
Compression=zip/5
DefaultDirName={pf}\Cinemaware Marquee\Darwinia
DefaultGroupName=Darwinia
LicenseFile=c:\development\Darwinia\docs\egamesEULA.txt
OutputBaseFilename=setup

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: checkablealone

[Files]
Source: "..\build\darwinia.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\main.dat"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\sounds.dat"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\language.dat"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\cinemaware.avi"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Darwinia"; Filename: "{app}\darwinia.exe"; WorkingDir: "{app}"
Name: "{group}\Cinemaware Marquee"; Filename: "http://www.cinemawaremarquee.com"
Name: "{group}\Darwinia Website"; Filename: "http://www.savedarwinia.com"
Name: "{group}\Introversion Software"; Filename: "http://www.introversion.co.uk"
Name: "{group}\{cm:UninstallProgram,Darwinia}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Darwinia"; Filename: "{app}\darwinia.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[UninstallDelete]
Type: files; Name: "{app}\darwinia.url"
Type: files; Name: "{app}\Preferences.txt"
Type: files; Name: "{app}\Blackbox.txt"
Type: filesandordirs; Name: "{app}\users"
