#include "homeassistant_switch.h"
#include "esphome/core/log.h"
#include "esphome/components/api/api_server.h"

namespace esphome {
namespace homeassistant {

static const char *const TAG = "homeassistant.switch";

void HomeassistantSwitch::setup() {
  api::global_api_server->subscribe_home_assistant_state(
      this->entity_id_, this->attribute_, [this](const std::string &state) {
        auto val = parse_on_off(state.c_str());
        switch (val) {
          case PARSE_NONE:
          case PARSE_TOGGLE:
            ESP_LOGW(TAG, "Can't convert '%s' to binary state!", state.c_str());
            break;
          case PARSE_ON:
          case PARSE_OFF:
            bool new_state = val == PARSE_ON;
            if (this->attribute_.has_value()) {
              ESP_LOGD(TAG, "'%s::%s': Got attribute state %s", this->entity_id_.c_str(),
                       this->attribute_.value().c_str(), ONOFF(new_state));
            } else {
              ESP_LOGD(TAG, "'%s': Got state %s", this->entity_id_.c_str(), ONOFF(new_state));
            }
            if (this->initial_) {
              this->publish_initial_state(new_state);
            } else {
              this->publish_state(new_state);
            }
            break;
        }
        this->initial_ = false;
      });
}
void HomeassistantSwitch::dump_config() {
  LOG_switch("", "Homeassistant Binary Sensor", this);
  ESP_LOGCONFIG(TAG, "  Entity ID: '%s'", this->entity_id_.c_str());
  if (this->attribute_.has_value()) {
    ESP_LOGCONFIG(TAG, "  Attribute: '%s'", this->attribute_.value().c_str());
  }
}
float HomeassistantSwitch::get_setup_priority() const { return setup_priority::AFTER_WIFI; }

}  // namespace homeassistant
}  // namespace esphome
