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

ScrollView {
    id: scannerScrollView
    anchors.fill: parent
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Flickable {
        anchors.fill: parent
   //     contentWidth: viewport.width

        property variant location: QtPositioning.coordinate(Api.gps.gpsLock ? Api.gps.latitude : 0, Api.gps.gpsLock ? Api.gps.longitude : 0)
        //! [Initialize Plugin]
        Plugin {
            id: myPlugin
            name: "osm"
            //specify plugin parameters if necessary
            //PluginParameter {...}
            //PluginParameter {...}
            //...
        }
        //! [Initialize Plugin]

        //! [Current Location]
//        PositionSource {
//            id: positionSource
//            property variant lastSearchPosition: location
//            active: true
//            updateInterval: 500//120000 // 2 mins
//            onPositionChanged:  {
//                var currentPosition = positionSource.position.coordinate
//                map.center = currentPosition
//                var distance = currentPosition.distanceTo(lastSearchPosition)
//                if (distance > 500) {
//                    // 500m from last performed pizza search
//                    lastSearchPosition = currentPosition
//                    searchModel.searchArea = QtPositioning.circle(currentPosition)
//                    searchModel.update()
//                }
//            }
//        }
        //! [Current Location]

        //! [PlaceSearchModel]
//        PlaceSearchModel {
//            id: searchModel

//            plugin: myPlugin

//            searchTerm: "Pizza"
//            //initially show Brisbane
//            searchArea: QtPositioning.circle(location)

//            Component.onCompleted: update()
//        }
        //! [PlaceSearchModel]

        //! [Places MapItemView]
        Map {
            id: map
            anchors.fill: parent
            plugin: myPlugin;
            center: QtPositioning.coordinate(Api.gps.gpsLock ? Api.gps.latitude : 0, Api.gps.gpsLock ? Api.gps.longitude : 0)
            zoomLevel: 13

//            MapItemView {
//                model: searchModel
//                delegate: MapQuickItem {
//                    coordinate: place.location.coordinate

//                    anchorPoint.x: image.width * 0.5
//                    anchorPoint.y: image.height

//                    sourceItem: Image {
//                        id: image
//                        source: "marker.png"
//                    }
//                }
//            }
        }
        //! [Places MapItemView]

//        Connections {
//            target: searchModel
//            onStatusChanged: {
//                if (searchModel.status == PlaceSearchModel.Error)
//                    console.log(searchModel.errorString());
//            }
//        }
    }
}
