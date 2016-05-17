#pragma once 

#include "PositionProviderPlugin.h"

class RpPositionProviderPluginPrivate;

class RpPositionProviderPlugin : public Marble::PositionProviderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.cappeen.RpPositionProviderPlugin" )
    Q_INTERFACES( Marble::PositionProviderPluginInterface )

public:
    RpPositionProviderPlugin();
    virtual ~RpPositionProviderPlugin();

    // Implementing PluginInterface
    virtual QString name() const;
    virtual QString nameId() const;
    virtual QString guiString() const;
    virtual QString version() const;
    virtual QString description() const;
    virtual QString copyrightYears() const;
    virtual QList<Marble::PluginAuthor> pluginAuthors() const;
    virtual QIcon icon() const;
    virtual void initialize();
    virtual bool isInitialized() const;
    virtual qreal speed() const;
    virtual qreal direction() const;
    virtual QDateTime timestamp() const;

    // Implementing PositionProviderPlugin
    virtual PositionProviderPlugin * newInstance() const;

    // Implementing PositionProviderPluginInterface
	virtual Marble::PositionProviderStatus status() const;
	virtual Marble::GeoDataCoordinates position() const;
	virtual Marble::GeoDataAccuracy accuracy() const;

private Q_SLOTS:
    void update();

private:
    RpPositionProviderPluginPrivate* const d;

};
