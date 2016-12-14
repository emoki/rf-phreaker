#include "MarbleModelPrimary.h"
#include "MarbleDebug.h"
#include "MarbleModel.h"

#include <mutex>

using namespace Marble;

class MarbleModelPrimaryPrivate {
public:
	static MarbleModelPrimaryPrivate& instance() {
		static MarbleModelPrimaryPrivate m;
		return m;
	}

	void setMarbleModel(MarbleModel* t) {
		std::lock_guard<std::mutex> lock(m);
		model = t;
	}

	MarbleModel* marbleModel() {
		std::lock_guard<std::mutex> lock(m);
		return model;
	}

private:
	MarbleModelPrimaryPrivate() : model(nullptr) {}
	MarbleModel *model;
	std::mutex m;
};

MarbleModelPrimary::MarbleModelPrimary()
	: d(0) {}


void MarbleModelPrimary::setMarbleModel(MarbleModel* model) {
	MarbleModelPrimaryPrivate::instance().setMarbleModel(model);
}

MarbleModel* MarbleModelPrimary::marbleModel() {
	return MarbleModelPrimaryPrivate::instance().marbleModel();
}
