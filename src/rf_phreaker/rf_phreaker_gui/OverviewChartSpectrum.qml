import QtQuick 2.6
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtCharts 2.1
import RfPhreaker 1.0

OverviewChart {
    id: _root
    property var spectrumManager
    xMin: spectrumManager === null || (spectrumManager.freqLimits.low < 300 || spectrumManager.freqLimits.low > 2600)
          ? 300 : spectrumManager.freqLimits.low - Math.round((spectrumManager.freqLimits.high - spectrumManager.freqLimits.low) * .05)
    xMax: spectrumManager === null || (spectrumManager.freqLimits.high > 2600 || spectrumManager.freqLimits.high < 300)
          ? 2600 : spectrumManager.freqLimits.high + Math.round((spectrumManager.freqLimits.high - spectrumManager.freqLimits.low) * .05)
    yMin: -140
    yMax: -10


    function update() {
        for(var i = 0; i < _root.count; ++i) {
            spectrumManager.updateLineSeries(_root.series(i), i);
        }
    }

    function create() {
        // Account for dummy series
        for(var i = _root.count; i < spectrumManager.numItems; ++i) {
            var line = _root.createSeries(ChartView.SeriesTypeLine, i,
                                                          _root.overviewAxisX, _root.overviewAxisY);
            line.useOpenGl = true;
        }
    }

    Timer {
        id: specRefresh
        interval: 300
        running: true
        repeat: true
        onTriggered: _root.update()
    }

    Connections {
        target: spectrumManager
        onNumItemsChanged: _root.create()
        onFinishedReset: {
            _root.removeAllSeries();
        }
    }

    Component.onCompleted: {
        _root.create();
        _root.update();
    }
}
