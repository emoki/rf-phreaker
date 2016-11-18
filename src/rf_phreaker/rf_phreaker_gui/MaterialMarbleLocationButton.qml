import QtQuick 2.5
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

ActionButton {
    id: location

    property MarbleManager marbleManager

    action: Action {
        text: "Locate and Track"
        shortcut: "Ctrl+L"
        onTriggered: {
            marbleManager.isTrackingEnabled = true;
            marbleManager.setCurrentTrackVisible(true);
            marbleManager.centerOnCurrentPosition();
        }
    }
    iconName: Api.connectionStatus === ApiTypes.CONNECTED
              ? (marbleManager.positionAvailable ? "device/gps_fixed" : "device/gps_fixed")
              : "device/gps_off"
}
