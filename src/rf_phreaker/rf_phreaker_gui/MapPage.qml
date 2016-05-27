import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtPositioning 5.3
import QtLocation 5.3
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0
import org.kde.edu.marble 0.20


Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"
    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: row
            Layout.preferredHeight: 30

            Button {
                id: downloadButton
                text: "Download"
                onClicked: {
                    marbleManager.downloadMapRegion(marbleManager.marbleMap);
                }
            }

            ProgressBar {
                value: marbleManager.downloadProgess;
            }
        }

        MarblePlacemarkList {
            Layout.preferredHeight: 125
            Layout.fillWidth: true
            model: marbleManager.placemarkModel
            manager: marbleManager
        }


        MarbleManager {
            id: marbleManager
            Layout.fillHeight: true
            Layout.fillWidth: true
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
                onPinchStarted: { marbleManager.handlePinchStart(pinch.center) }
                onPinchUpdated: { marbleManager.handlePinchUpdate(pinch.center, pinch.scale) }
                onPinchFinished:{ marbleManager.handlePinchEnd(pinch.center, false) }
            }
            PositionMarker {
                id: positionMarker
                angle: marbleManager.angle
                visible: marbleManager.positionVisible && marbleManager.iscurrentPositionGloballyVisible
                function update() {
                    var newX = Math.floor(marbleManager.screenCoordinatesFromCoordinate(marbleManager.currentPosition.coordinate).x);
                    var newY = Math.floor(marbleManager.screenCoordinatesFromCoordinate(marbleManager.currentPosition.coordinate).y);
                    if(newX !== posX || newY !== posY) {
                        if((Math.abs(newX - posX) > 0 || Math.abs(newY - posY) > 0) && marbleManager.isTrackingEnabled && visible) {
                            posX = newX;
                            posY = newY;
                            marbleManager.centerOnCurrentPosition();
                        }
                        else {
                            posX = newX;
                            posY = newY;
                        }
                    }
                }
            }

            PositionButton {
                id: zoomToPositionButton
                anchors {
                    right: parent.right
                    rightMargin: 0.005 * root.width
                    bottom: marbleManager.bottom
                    bottomMargin: 10
                }

                iconSource: marbleManager.positionAvailable ? "qrc:/icons/device_gps_fixed.svg" : "qrc:/icons/device_gps_fixed.svg"

                onClicked: {
                    marbleManager.isTrackingEnabled = true;
                    marbleManager.setCurrentTrackVisible(true);
                    marbleManager.centerOnCurrentLocation();
                }

                property real distance: 0

                function updateIndicator() {
                    var point = marbleManager.mapFromItem(zoomToPositionButton, diameter * 0.5, diameter * 0.5);
                    distance = 0.001 * marbleManager.distanceFromPointToCurrentLocation(point);
                    angle = marbleManager.angleFromPointToCurrentLocation(point);
                }

                showDirection: marbleManager.positionAvailable && !marbleManager.positionVisible
            }
        }
    }
}
