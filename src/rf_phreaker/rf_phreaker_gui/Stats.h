#include <QMap>
#include <stdint.h>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker.pb.h"

//namespace rf_phreaker { namespace gui {


class Stats {
public:
	void start_benchmark(const std::string &filename) {
		benchmark_.open_benchmark(filename + "_benchmark.txt", true);
		count_.clear();
		benchmark_.clear();
		benchmark_.start_timer();
	}

	void stop_benchmark() {
		benchmark_.stop_timer();
		double t = boost::chrono::duration_cast<boost::chrono::seconds>(boost::chrono::nanoseconds(benchmark_.total_time_elapsed().wall)).count();
		QString s;
		s.append("\ngsm_full_scan\t").append(QString::number(count_[rf_phreaker::GSM_LAYER_3_DECODE])).append("\t")
			.append(QString::number(count_[rf_phreaker::GSM_LAYER_3_DECODE] / t));
		s.append("\nwcdma_full_scan\t").append(QString::number(count_[rf_phreaker::UMTS_LAYER_3_DECODE])).append("\t")
			.append(QString::number(count_[rf_phreaker::UMTS_LAYER_3_DECODE] / t));
		s.append("\nlte_full_scan\t").append(QString::number(count_[rf_phreaker::LTE_LAYER_3_DECODE])).append("\t")
			.append(QString::number(count_[rf_phreaker::LTE_LAYER_3_DECODE] / t));
		s.append("\ngsm_sweep\t").append(QString::number(count_[rf_phreaker::GSM_SWEEP])).append("\t")
			.append(QString::number(count_[rf_phreaker::GSM_SWEEP] / t));
		s.append("\nwcdma_sweep\t").append(QString::number(count_[rf_phreaker::UMTS_SWEEP])).append("\t")
			.append(QString::number(count_[rf_phreaker::UMTS_SWEEP] / t));
		s.append("\nlte_sweep\t").append(QString::number(count_[rf_phreaker::LTE_SWEEP])).append("\t")
			.append(QString::number(count_[rf_phreaker::LTE_SWEEP] / t));
		benchmark_.output_total_time_elapsed(s.toStdString());
		benchmark_.close_benchmark();
	}

	void update_benchmark(rf_phreaker::protobuf::rp_update::UpdateCase t) {
		switch(t) {
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLog:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGps:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan:
			count_[rf_phreaker::GSM_LAYER_3_DECODE]++;
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan:
			count_[rf_phreaker::UMTS_LAYER_3_DECODE]++;
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan:
			count_[rf_phreaker::LTE_LAYER_3_DECODE]++;
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep:
			count_[rf_phreaker::GSM_SWEEP]++;
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep:
			count_[rf_phreaker::UMTS_SWEEP]++;
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep:
			count_[rf_phreaker::LTE_SWEEP]++;
			break;
		default:
			qDebug() << "Unknown protobuf message.";
		}
	}

private:
	QMap<rf_phreaker::specifier, int64_t> count_;
	rf_phreaker::benchmark benchmark_;
};


//}}