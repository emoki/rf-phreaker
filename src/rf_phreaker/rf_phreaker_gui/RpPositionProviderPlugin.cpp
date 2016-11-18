#include "RpPositionProviderPlugin.h"
#include <QTimer>
#include <QIcon>
#include "GeoDataAccuracy.h"
#include "marble_export.h"
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"

using namespace Marble;

class RpPositionProviderPluginPrivate
{
public:
	RpPositionProviderPluginPrivate()
		: m_status(PositionProviderStatusUnavailable)
		, isInitialized_(false) {}

	~RpPositionProviderPluginPrivate() {}

	Gps gps_;
	PositionProviderStatus m_status;
	bool isInitialized_;
};


QString RpPositionProviderPlugin::name() const {
	return tr("RF Phreaker Position Provider Plugin");
}

QString RpPositionProviderPlugin::nameId() const {
	return "RfPhreakerPositioning";
}

QString RpPositionProviderPlugin::guiString() const {
	return tr("RF Phreaker Positioning Location");
}

QString RpPositionProviderPlugin::version() const {
	return "1.0";
}

QString RpPositionProviderPlugin::description() const {
	return tr("Reports the GPS position of a RF Phreaker compatible device.");
}

QString RpPositionProviderPlugin::copyrightYears() const {
	return "2016";
}

QVector<PluginAuthor> RpPositionProviderPlugin::pluginAuthors() const {
	return QVector<PluginAuthor>()
		<< PluginAuthor("Ethan Steffens", "esteffens.cappeen@gmail.com");
}

QIcon RpPositionProviderPlugin::icon() const {
	return QIcon();
}

PositionProviderPlugin* RpPositionProviderPlugin::newInstance() const {
	return new RpPositionProviderPlugin;
}

PositionProviderStatus RpPositionProviderPlugin::status() const {
	return d->m_status;
}

GeoDataCoordinates RpPositionProviderPlugin::position() const {
	if(d->m_status == PositionProviderStatusAvailable && d->gps_.gpsLock())
		return GeoDataCoordinates(d->gps_.longitude(), d->gps_.latitude(),
		d->gps_.altitude(), GeoDataCoordinates::Degree);
	else
		return GeoDataCoordinates();
}

GeoDataAccuracy RpPositionProviderPlugin::accuracy() const {
	if(d->m_status == PositionProviderStatusAvailable && d->gps_.gpsLock())
		return GeoDataAccuracy(GeoDataAccuracy::Detailed, d->gps_.horizontalAccuracyMeters(), d->gps_.verticalAccuracyMeters());
	else
		return GeoDataAccuracy();
}

RpPositionProviderPlugin::RpPositionProviderPlugin() :
d(new RpPositionProviderPluginPrivate) {}

RpPositionProviderPlugin::~RpPositionProviderPlugin() {
	delete d;
}

void RpPositionProviderPlugin::initialize() {
	QObject::connect(Api::instance(), &Api::gpsChanged, this, &RpPositionProviderPlugin::update);
	QObject::connect(Api::instance(), &Api::connectionStatusChanged, this, &RpPositionProviderPlugin::update);
}

bool RpPositionProviderPlugin::isInitialized() const {
	return d->isInitialized_;
}

qreal RpPositionProviderPlugin::speed() const {
	if(d->m_status == PositionProviderStatusAvailable && d->gps_.gpsLock())
		return d->gps_.speed();
	else
		return 0.0;
}

qreal RpPositionProviderPlugin::direction() const {
	if(d->m_status == PositionProviderStatusAvailable && d->gps_.gpsLock())
		return d->gps_.angle();
	else
		return 0.0;
}

QDateTime RpPositionProviderPlugin::timestamp() const {
	if(d->m_status == PositionProviderStatusAvailable)
		return d->gps_.utcDateTime();
	else
		return QDateTime();
}

void RpPositionProviderPlugin::update() {
	auto connectionStatus = Api::instance()->connectionStatus();
	auto gps = Api::instance()->gps();
	auto newStatus = PositionProviderStatusAcquiring;

	if(connectionStatus == ApiTypes::CONNECTED) {
		d->gps_.copy(*Api::instance()->gps());
		if(d->gps_.gpsLock())
			newStatus = PositionProviderStatusAvailable;
		else
			newStatus = PositionProviderStatusAcquiring;
	}
	else {
		newStatus = PositionProviderStatusUnavailable;
	}

	if(newStatus != d->m_status) {
		d->m_status = newStatus;
		emit statusChanged(newStatus);
	}
	if(newStatus == PositionProviderStatusAvailable)
		emit positionChanged(position(), accuracy());
}


#if QT_VERSION >= QT_VERSION_CHECK( 5, 0, 0 )
#if defined(Q_EXPORT_PLUGIN)
#undef Q_EXPORT_PLUGIN
#undef Q_EXPORT_PLUGIN2
#endif

#define Q_EXPORT_PLUGIN(a)
#define Q_EXPORT_PLUGIN2(a, b)
#else
# define Q_PLUGIN_METADATA(a)
#endif

Q_EXPORT_PLUGIN2(RpPositionProviderPlugin, RpPositionProviderPlugin)

