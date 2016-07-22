
var gui_name = "rf_phreaker_gui"

// Skip all pages and go directly to finished page.
// (see also componenterror example)
function cancelInstaller(message)
{
    installer.setDefaultPageVisible(QInstaller.Introduction, false);
    installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
    installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
    installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
    installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
    installer.setDefaultPageVisible(QInstaller.PerformInstallation, false);
    installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);

    var abortText = "<font color='red'>" + message +"</font>";
    installer.setValue("FinishedText", abortText);
}

function Component()
{}

Component.prototype.createOperations = function()
{   
	component.createOperations();
	
    if (systemInfo.productType === "windows") {
		component.addOperation("CreateShortcut",
                            "@TargetDir@/rf_phreaker_gui.exe",
                            "@StartMenuDir@/RF Phreaker.lnk",
							"workingDirectory=@TargetDir@", 
							"iconPath=%SystemRoot%/system32/SHELL32.dll",
							"iconId=2");
		
		//var app_data_loc = QDesktopServices.storageLocation(QDesktopServices.AppConfigLocation);
		// Hack to get roaming path.
		var app_data_loc = installer.value("UserStartMenuProgramsPath");
		app_data_loc = app_data_loc.substr(0, app_data_loc.search("Microsoft"));
		app_data_loc = app_data_loc + "rf_phreaker";
		component.addOperation("Mkdir", app_data_loc);
		component.addOperation("Move", "@TargetDir@/gui.ini", app_data_loc + "/gui.ini");
		component.addOperation("Move", "@TargetDir@/rf_phreaker_api.ini", app_data_loc + "/rf_phreaker_api.ini");
	}
}