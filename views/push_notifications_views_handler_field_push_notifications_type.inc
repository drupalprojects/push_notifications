<?php

/**
 * Field handler to display push notifications type.
 */
class push_notifications_views_handler_field_push_notifications_type extends views_handler_field {
  //@TODO: Add a config to show raw or friendly values?
  function render($values) {
    $token_type = $this->get_value($values);
    return $this->get_token_type_name($token_type);
  }
  function get_token_type_name($type){
    // Build an array of types, as defined by the Push Notifications module.
    $valid_types = array(
      PUSH_NOTIFICATIONS_TYPE_ID_IOS => 'iOS',
      PUSH_NOTIFICATIONS_TYPE_ID_ANDROID => 'Android',
    );
    if (isset($valid_types[$type])){
      return $valid_types[$type];
    }
    return '';
  }
}
