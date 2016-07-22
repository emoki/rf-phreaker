import QtQuick 2.6
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtCharts 2.1
import RfPhreaker 1.0

ChartView {
    id: overviewChart
    property var xMin: Api.lowestFreq
    property var xMax: Api.highestFreq
    property var yMin: -130
    property var yMax: 0
    property alias sweepModelList: sweepLines.sourceModel
    property alias channelModel: channelSweepLines.sourceModel

    margins {
        right: 0
        left: 0
        top: 0
        bottom: 0
    }

    //title: "Spectrum Overview"
    antialiasing: true
    animationOptions: ChartView.NoAnimation
    //theme: ChartView.ChartThemeDark
    legend.visible: false
    focus: true

    Timer {
        interval: 200
        running: true
        repeat: true
        onTriggered: {
            if(overviewAxisX.max > overviewChart.xMax) overviewAxisX.max = overviewChart.xMax;
            if(overviewAxisX.max < overviewChart.xMin) overviewAxisX.max = overviewChart.xMin + 1;
            if(overviewAxisX.min > overviewChart.xMax) overviewAxisX.min = overviewChart.xMax - 1;
            if(overviewAxisX.min < overviewChart.xMin) overviewAxisX.min = overviewChart.xMin;
            if(overviewAxisY.max > overviewChart.yMax) overviewAxisY.max = overviewChart.yMax;
            if(overviewAxisY.max < overviewChart.yMin) overviewAxisY.max = overviewChart.yMin + 1;
            if(overviewAxisY.min > overviewChart.yMax) overviewAxisY.min = overviewChart.yMax - 1;
            if(overviewAxisY.min < overviewChart.yMin) overviewAxisY.min = overviewChart.yMin;
        }
    }

    ValueAxis {
        id: overviewAxisX
        min: xMin
        max: xMax
        gridVisible: true
        minorGridVisible: true
    }
    ValueAxis {
        id: overviewAxisY
        min: yMin
        max: yMax
        gridVisible: true
        minorGridVisible: true
    }
    LineSeries{
        id: dummy
        axisX: overviewAxisX
        axisY: overviewAxisY
    }
    SweepLines {
        id: sweepLines
        chart: overviewChart
        mainAxisX: overviewAxisX
        mainAxisY: overviewAxisY
        //sourceModel: Api.sweepModelList
    }
    ChannelSweepLines {
        id: channelSweepLines
        chart: overviewChart
        mainAxisX: overviewAxisX
        mainAxisY: overviewAxisY
        //sourceModel: Api.highestCellPerChannelModel
    }

    Rectangle {
        id: zoomRect
        property real xScale: 1
        property real yScale: 1
        property bool inUse: false
        visible: false
        color: "#6ac5e8"
        opacity: 0.35
        z: 100
        width: 1
        height: 1
        transform: Scale {
            xScale: zoomRect.xScale
            yScale: zoomRect.yScale
        }
    }

    MouseArea {
        anchors.fill:parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
        onWheel: {
            //console.debug("onwheel");
            if (wheel.angleDelta.y > 0)
                overviewChart.zoom(1.25);
            else
                overviewChart.zoom(.75);
        }
        onPressed: {
            zoomRect.xScale = 1;
            zoomRect.yScale = 1;
            zoomRect.x = mouse.x
            zoomRect.y = mouse.y
            if(mouse.button === Qt.LeftButton || mouse.button === Qt.RightButton) {
                zoomRect.visible = true;
                zoomRect.inUse = true;
            }
            else if(mouse.button === Qt.MiddleButton)
                    zoomRect.inUse = true;
        }
        onPositionChanged: {
            if(zoomRect.inUse) {
                zoomRect.xScale = mouse.x - zoomRect.x;
                zoomRect.yScale = mouse.y - zoomRect.y;
                //console.debug(mouse.button);
                //console.debug(mouse.buttons);
                if(mouse.buttons & Qt.MiddleButton) {
                    overviewChart.scrollRight(zoomRect.x - mouse.x);
                    overviewChart.scrollUp(mouse.y - zoomRect.y);
                    zoomRect.xScale = 1;
                    zoomRect.yScale = 1;
                    zoomRect.x = mouse.x
                    zoomRect.y = mouse.y
                }
            }
        }
        onReleased: {
            var x = Math.min(zoomRect.x, mouse.x);
            var y = Math.min(zoomRect.y, mouse.y);
            var width = Math.max(zoomRect.x, mouse.x) - x;
            var height = Math.max(zoomRect.y, mouse.y) - y;

            if(mouse.button === Qt.LeftButton)
                overviewChart.zoomIn(Qt.rect(x, y, width, height));
            else if(mouse.button == Qt.RightButton) {
                //console.debug(width * height, " ", overviewChart.width * overviewChart.height, " ", (width * height) / (overviewChart.width * overviewChart.height))
                overviewChart.zoom(Math.min(.6, Math.max(.9, 100 * (width * height) / (overviewChart.width * overviewChart.height))));
            }
            zoomRect.visible = false;
            zoomRect.inUse = false;
        }
    }

    Keys.onPressed: {
       // console.debug("fucking key bitch!");
        if(event.key === Qt.Key_Plus) {
            overviewChart.zoom(1.5);
            event.accepted = true;
        }
        else if(event.key === Qt.Key_Minus) {
            overviewChart.zoom(.5);
            event.accepted = true;
        }
        else if(event.key === Qt.Key_Left) {
            overviewChart.scrollLeft(50)();
            event.accepted = true;
        }
        else if(event.key === Qt.Key_Right) {
            overviewChart.scrollRight(50);
            event.accepted = true;
        }
        else if(event.key === Qt.Key_Up) {
            overviewChart.scrollUp(50);
            event.accepted = true;
        }
        else if(event.key === Qt.Key_Down) {
            overviewChart.scrollDown(50);
            event.accepted = true;
        }
    }
}
