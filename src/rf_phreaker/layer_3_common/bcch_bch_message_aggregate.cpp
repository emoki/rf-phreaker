#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"

using namespace layer_3_information;

bcch_bch_message_aggregate::bcch_bch_message_aggregate()
: mcc_(not_decoded_32), mnc_(not_decoded_32), lac_(not_decoded_32), cid_(not_decoded_32), unique_sector_key_(0) {}
