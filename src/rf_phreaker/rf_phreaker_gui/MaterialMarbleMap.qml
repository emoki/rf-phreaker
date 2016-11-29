import QtQuick 2.5
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

Item {
    id: root_
    property alias marbleManager: manager
    property alias layerPopup: layerPopup__
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

    PopupBase {
        id: layerPopup__

        x: root_.x + root_.width / 2 - marblePlacemarkList.width / 2
        y: root_.y + dp(64)

        width: marblePlacemarkList.implicitWidth
        height: marblePlacemarkList.implicitHeight

        globalMouseAreaEnabled: false
        dismissOnTap: false

        opacity: showing ? 1 : 0
        visible: opacity > 0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        View {
            id: dialogContainer

            anchors.fill: parent
            elevation: 5
            radius: dp(2)

            Flickable {
                id: viewFlick
                MaterialMarblePlacemarkList {
                    id: marblePlacemarkList
                    manager: manager
                    model: manager.placemarkModel
                    snackbar: page.snackbar
                    onClose: layerPopup.close()
                }
            }
            Scrollbar {
                flickableItem: viewFlick
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
