import QtQuick 2.5
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

Item {
    property alias marbleManager: manager
    height: 600
    width: 600

    Component.onCompleted: {
        if(Api.connectionStatus === ApiTypes.CONNECTED && marbleManager.positionAvailable) {
            manager.isTrackingEnabled = true;
            manager.centerOnCurrentPosition();
        }
    }

    MarbleManager {
        id: manager
        anchors.fill: parent
        visible: true
        focus: true

        projection: MarbleItem.Mercator
        //mapThemeId: "earth/vectorosm/vectorosm.dgml"
        mapThemeId: "earth/openstreetmap/openstreetmap.dgml"
        showFrameRate: false
        showAtmosphere: false
        showCompass: false
        showClouds: false
        showCrosshairs: false
        showGrid: false
        showOverviewMap: false
        showOtherPlaces: false
        showScaleBar: false
        showBackground: false
        positionProvider: "RfPhreakerPositioning"
        showPositionMarker: true

        onCurrentPositionChanged: {
            positionMarker.update();
        }
        onVisibleLatLonAltBoxChanged: {
            positionMarker.update();
        }

        PinchArea
        {
            objectName: "pinchArea"
            anchors.fill: parent
            onPinchStarted: { manager.handlePinchStart(pinch.center) }
            onPinchUpdated: { manager.handlePinchUpdate(pinch.center, pinch.scale) }
            onPinchFinished:{ manager.handlePinchEnd(pinch.center, false) }
        }
        PositionMarker {
            id: positionMarker
            angle: manager.angle
            visible: manager.positionVisible && manager.iscurrentPositionGloballyVisible
            function update() {
                var screenCoordinate = manager.currentPositionScreenCoordinates();
                var newX = Math.floor(screenCoordinate.x);
                var newY = Math.floor(screenCoordinate.y);
                if(newX !== posX || newY !== posY) {
                    if((Math.abs(newX - posX) > 0 || Math.abs(newY - posY) > 0) && manager.isTrackingEnabled && visible) {
                        posX = newX;
                        posY = newY;
                        manager.centerOnCoordinates(manager.currentPosition.longitude, manager.currentPosition.latitude);
                    }
                    else {
                        posX = newX;
                        posY = newY;
                    }
                    manager.update();
                }
            }
        }
    }

    ProgressBar {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "transparent"
        value: manager.downloadProgess
    }
}
