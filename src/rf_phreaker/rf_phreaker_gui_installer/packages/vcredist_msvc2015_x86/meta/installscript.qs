
// constructor
function Component()
{
    // only install c runtime if it is needed, no minor version check of the c runtime till we need it
    if (installer.value("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\x86\\Installed") != 1)
        component.setValue("RequiresAdminRights", "true");
}

Component.prototype.createOperations = function()
{
    // Call the base createOperations and afterwards set some registry settings
    // so that the simulator finds its fonts and applications find the simulator
    component.createOperations();

    if (installer.value("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\x86\\Installed") != 1) {
        // return value 3010 means it need a reboot, but in most cases it is not needed for run Qt application
        // return value 5100 means there's a newer version of the runtime already installed
        component.addElevatedOperation("Execute", "{0,3010,1638,5100}", "@TargetDir@\\vcredist\\vcredist_msvc2015_x86.exe", "/norestart", "/q");
    }
}
