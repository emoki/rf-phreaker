
// constructor
function Component()
{
    // only install c runtime if it is needed, no minor version check of the c runtime till we need it
	component.setValue("RequiresAdminRights", "true");
}

function majorMinorVersion(str)
{
    var arr = str.split(".", 2);
	if(arr.length > 1)
		return arr[0] + "." + arr[1];
	else
		return arr[0];
		
}

Component.prototype.createOperations = function()
{
    // Call the base createOperations and afterwards set some registry settings
    // so that the simulator finds its fonts and applications find the simulator
    component.createOperations();

    if (systemInfo.kernelType !== "winnt") {
		QMessageBox["warning"]( "Error" , "Error", "Windows only!");
        return;
	}
		
	var arch_dir = "x86";
	var dp_inst = "DPInst_x86.exe"
	if (systemInfo.currentCpuArchitecture == "x86_64") {
		arch_dir = "x64";
		dp_inst = "DPInst_amd64.exe";
	}
	
	var win_dir;
	var version = majorMinorVersion(systemInfo.kernelVersion);
	if (version == "5.1" || version == "5.2")
		win_dir = "wxp";
	else if (version == "6.0")
		win_dir = "vista";
	else if (version == "6.1")
		win_dir = "win7";
	else if (version == "6.2")
		win_dir = "win8";
	else if (version == "6.3" || version == "10.0")
		win_dir = "win81";
	
	var driver_path = "@TargetDir@\\cypress_usb3\\" + win_dir + "\\" + arch_dir;
	var exe_string =  "@TargetDir@/cypress_usb3/" + dp_inst;

	//if(installer.value()) {
		component.addElevatedOperation("Execute", "{0,1,2,1073741826,256,-2147418112,-1073676287}", exe_string, "/lm", "/path", driver_path);
	//}
}
