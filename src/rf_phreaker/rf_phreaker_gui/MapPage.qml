import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtPositioning 5.3
import QtLocation 5.3
import RfPhreaker 1.0
import org.kde.edu.marble 0.20


Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"

//    function centerOnGps() {
//        if(Api.gps.gpsLock && MarbleManager.isTracking) {
//            marble.centerOn(Api.gps.longitude, Api.gps.latitude);
//            if(marble.zoom() > 50)
//                marble.setZoom(20, )
//        }

//    }

//    Timer {
//        interval: 1000
//        repeat: true
//        onTriggered: {
//        }
//    }

    // Change to MarbleItem after Marble has developed it more.
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            id: row
            Layout.preferredHeight: 30
            CheckBox {
                id: breadCrumb
                text: "Show Bread Crumb"
            }

            Button {
                id: trackMe
                text: "Where am I?!?"
                onClicked: MarbleManager.isTracking = true;
            }
            Button {
                id: downloadButton
                text: "Download"
                onClicked: {
                    MarbleManager.downloadMapRegion(marble.marbleMap);
                }
            }
            ProgressBar {
                value: MarbleManager.downloadProgess;
            }
        }

        MarbleWidget {
            id: marble
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: true
            focus: true

            Component.onCompleted: {
                // Our position provider is added manually wihtin MarbleManager init.
                MarbleManager.marbleMap = marble.marbleMap;
                marble.positionProvider = "RfPhreakerPositioning"
//				positionSource.map = marble;
//				tracking.map = marble;
            }

            PinchArea
            {
                anchors.fill: parent
                enabled: true
                objectName: "pinchArea"
                onPinchStarted: { marble.handlePinchStart(pinch.center) }
                onPinchUpdated: { marble.handlePinchUpdate(pinch.center, pinch.scale) }
                onPinchFinished:{ marble.handlePinchEnd(pinch.center, false) }
            }
            showFrameRate: false
            projection: MarbleItem.Mercator
            mapThemeId: "earth/openstreetmap/openstreetmap.dgml"
            showAtmosphere: false
            showCompass: false
            showClouds: false
            showCrosshairs: false
            showGrid: false
            showOverviewMap: false
            showOtherPlaces: false
            showScaleBar: false
            showBackground: false

       }
        //			 Tracking {
        //				id: tracking
        //				showTrack: true
        //				autoCenter: true
        //				autoZoom: true
        //				positionMarkerType: Tracking.Circle
        //				positionSource: PositionSource {
        //					id: positionSource
        //					source: "RfPhreakerPositioning"
        //					active: true
        //				}
        //			}
    }
}
