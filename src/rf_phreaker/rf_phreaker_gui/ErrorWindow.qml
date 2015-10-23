import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Window 2.2
import RfPhreaker 1.0

Dialog {
    id: openScannerWindow
    width: 16*20
    height: 10*20
    title: "Error"
    signal canceled()
    signal accepted()

    flags: Qt.Dialog
    modality: Qt.WindowModal

}

