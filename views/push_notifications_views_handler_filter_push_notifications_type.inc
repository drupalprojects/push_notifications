<?php

/**
 * Provides type filter options for the token type.
 */
class push_notifications_views_handler_filter_push_notifications_type extends views_handler_filter_in_operator {
  /**
   * Compute type filter options.
   */
  public function get_value_options() {
    if (!isset($this->value_options)) {
      $options = array(
        PUSH_NOTIFICATIONS_TYPE_ID_IOS => 'iOS',
        PUSH_NOTIFICATIONS_TYPE_ID_ANDROID => 'Android',
      );
      $this->value_options = $options;
    }
  }
}
