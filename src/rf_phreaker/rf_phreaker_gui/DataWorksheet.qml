import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

Item {
    anchors.fill: parent

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        TableView {
            id: umtsList
            height: parent.height / 2
            width: parent.width
            model: Api.wcdmaList

            TableViewColumn {
                title: "Freq"
                role: "carrierFreq"
            }
            TableViewColumn {
                title: "UARFCN"
                role: "uarfcn"
            }
            TableViewColumn {
                title: "CPICH"
                role: "cpich"
            }
            TableViewColumn {
                title: "Ec/Io"
                role: "ecio"
            }
            TableViewColumn {
                title: "RSCP"
                role: "rscp"
            }
        }
        TableView {
            id: lteList
            height: parent.height / 2
            width: parent.width
            model: Api.lteList

            TableViewColumn {
                title: "Freq"
                role: "carrierFreq"
            }
            TableViewColumn {
                title: "EARFCN"
                role: "earfcn"
            }

            TableViewColumn {
                title: "Bandwidth"
                role: "downlinkBandwidth"
            }
            TableViewColumn {
                title: "PhysCellID"
                role: "physicalCellID"
            }
            TableViewColumn {
                title: "SyncQuality"
                role: "syncQuality"
            }
            TableViewColumn {
                title: "CarrierSL"
                role: "carrierSignalLevel"
            }
        }
    }
}
